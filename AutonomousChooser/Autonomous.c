#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "menu_helper.h"

void initializeRobot()
{
	return;
}

task main()
{
	initializeRobot();

	bDisplayDiagnostics = false;
	StartTask(runMenu);

	waitForStart(); // Wait for the beginning of autonomous phase.

	StopTask(runMenu);
	eraseDisplay();
	bDisplayDiagnostics = true;

	wait1Msec(delay*1000);

	//Use the variables to run your auto here
}
