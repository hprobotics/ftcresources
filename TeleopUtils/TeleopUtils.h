#pragma SystemFile

//For more precise joystick control, use these names (i.e. leftjoy1_y) instead of joystick.[name] (i.e. joystick.joy1_y1)
int sign(int num){return (num<0)?-1:1;}
#define leftjoy1_y joystick.joy1_y1*joystick.joy1_y1*100.0/(128.0*128.0)*sign(joystick.joy1_y1)
#define rightjoy1_y joystick.joy1_y2*joystick.joy1_y2*100.0/(128.0*128.0)*sign(joystick.joy1_y2)
#define leftjoy2_y joystick.joy2_y1*joystick.joy2_y1*100.0/(128.0*128.0)*sign(joystick.joy2_y1)
#define rightjoy2_y joystick.joy2_y2*joystick.joy2_y2*100.0/(128.0*128.0)*sign(joystick.joy2_y2)
#define leftjoy1_x joystick.joy1_x1*joystick.joy1_x1*100.0/(128.0*128.0)*sign(joystick.joy1_x1)
#define rightjoy1_x joystick.joy1_x2*joystick.joy1_x2*100.0/(128.0*128.0)*sign(joystick.joy1_x2)
#define leftjoy2_x joystick.joy2_x1*joystick.joy2_x1*100.0/(128.0*128.0)*sign(joystick.joy2_x1)
#define rightjoy2_x joystick.joy2_x2*joystick.joy2_x2*100.0/(128.0*128.0)*sign(joystick.joy2_x2)

//use these values with joy1Btn(btn_number) and joy2Btn(btn_number) (i.e. joy1Btn(btn_RB))
enum joybtn
{
	btn_X=1,
	btn_A=2,
	btn_B=3,
	btn_Y=4,
	btn_LB=5,
	btn_RB=6,
	btn_LT=7,
	btn_RT=8,
	btn_BACK=9,
	btn_START=10
};

/* To create an easy to use toggle, adjust the following code for your application:
toggle myToggle; //create a toggle named myToggle
myToggle.active = false; //set the initial value
checkToggle(myToggle,joy1Btn(btn_Y)); //update the toggle state using btn_Y on joystick 1
if(myToggle.active){
	//do something when the toggle is active (like run a motor)
} else {
	//do something else when the toggle is inactive (like stop a motor)
}
*/

typedef struct
{
	bool pressed;
	bool active;
} toggle;

void checkToggle(toggle *mytoggle,short state){
	if((state)&&!mytoggle->pressed)
	{
		mytoggle->pressed=true;
		mytoggle->active=mytoggle->active;
	}
	if(!(state))
	{
		mytoggle->pressed=false;
	}
}
