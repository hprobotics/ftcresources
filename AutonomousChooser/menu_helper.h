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
	int startVal;

	currVar = &menu[0];

	eraseDisplay();

	while(true){
		int oldStartVal = startVal;
		startVal=floor(idx/4.0)*4;
		if(startVal!=oldStartVal){
			eraseDisplay();
		}
	int endVal=(menuLength-floor(idx/4.0)*4>4)?4:menuLength-floor(idx/4.0)*4;
		for(int i=startVal;i<endVal+startVal;i++){
			int linenum=i-startVal;
			if(menu[i].type=='b'){
				nxtDisplayString(linenum,"%s",menu[i].name);
				bool set =((bool)(*(menu[i].var)));
			string disp = set?(string)(menu[i].trueDisp):(string)(menu[i].falseDisp);
				nxtDisplayStringAt(60,63-linenum*8,"%s",disp);
				} else if(menu[i].type=='i'){
				nxtDisplayString(linenum,menu[i].name);
				nxtDisplayStringAt(80,63-linenum*8,"%2i",*(menu[i].var));
			}
			if(currVar->var==menu[i].var){
				nxtDisplayStringAt(94,63-linenum*8,"*");
				} else {
				nxtDisplayStringAt(94,63-linenum*8," ");
			}
		}

		if(floor((menuLength-1)/4.0)>0){
			nxtDisplayStringAt(0, 29, "Page %i/%i", floor(idx/4.0)+1, floor((menuLength-1)/4.0)+1);
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
