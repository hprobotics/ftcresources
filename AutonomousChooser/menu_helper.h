TButtons NEXT_BTN = kRightButton;
TButtons PREV_BTN = kLeftButton;
TButtons CAT_BTN = kEnterButton;

typedef struct {
	char corrupt;
	string name;
	char type;
	void* var;
	int min;
	int max;
	string trueDisp;
	string falseDisp;
} menuParameter;

int menuLength;

menuParameter* menu;

void switchBool(bool *ptr, TButtons btn);
void switchInt(int *ptr, TButtons btn, int min, int max);

task runMenu()
{
	menuParameter* currVar;
	int idx = 0;

	currVar = &menu[0];

	while(true){
		for(int i=0;i<menuLength;i++){
			if(menu[i].type=='b'){
				nxtDisplayString(i,"%s",menu[i].name);
				bool set =((bool)(*(menu[i].var)));
				string disp = set?(string)(menu[i].trueDisp):(string)(menu[i].falseDisp);
				nxtDisplayStringAt(60,63-i*8,"%s",disp);
				} else if(menu[i].type=='i'){
				nxtDisplayString(i,menu[i].name);
				nxtDisplayStringAt(80,63-i*8,"%2i",*(menu[i].var));
			}
			if(currVar->var==menu[i].var){
				nxtDisplayStringAt(94,63-i*8,"*");
				} else {
				nxtDisplayStringAt(94,63-i*8," ");
			}
		}

		if(nNxtButtonPressed==NEXT_BTN||nNxtButtonPressed==PREV_BTN){
			if(currVar->type=='b'){
				switchBool(currVar->var,nNxtButtonPressed);
				} else if (currVar->type=='i') {
				switchInt(currVar->var,nNxtButtonPressed,currVar->min,currVar->max);
			}
			ClearTimer(T1);
			while(nNxtButtonPressed!=kNoButton&&time1[T1]<=400);
		}

		if(nNxtButtonPressed==CAT_BTN){
			idx++;
			if(idx>=menuLength){
				idx = 0;
			}
			currVar = &menu[idx];
			ClearTimer(T1);
			while(nNxtButtonPressed!=kNoButton&&time1[T1]<=400);
		}

		//this section is copied from JoystickDriver.c with changed line numbers
		if ( externalBatteryAvg < 0){
			nxtDisplayTextLine(6, "Ext Batt: OFF");       //External battery is off or not connected
			} else {
			nxtDisplayTextLine(6, "Ext Batt:%4.1f V", externalBatteryAvg / (float) 1000);
		}
		nxtDisplayTextLine(7, "NXT Batt:%4.1f V", nAvgBatteryLevel / (float) 1000);   // Display NXT Battery Voltage
	}
}

void switchBool(bool *ptr, TButtons btn)
{
	if(btn == NEXT_BTN||btn == PREV_BTN)
	{
		*ptr=!*ptr;
	}
}

void switchInt(int *ptr, TButtons btn, int min, int max)
{
	if(btn == NEXT_BTN){
		*ptr=*ptr+1;
		} else if(btn == PREV_BTN) {
		*ptr=*ptr-1;
	}
	if(*ptr<min){
		*ptr=min;
		} else if(*ptr>max){
		*ptr = max;
	}
}
