#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
inertial Inertial = inertial(PORT9);

motor leftDrive1 = motor(PORT1, ratio6_1, false);
motor leftDrive2 = motor(PORT2, ratio6_1, true);
motor leftDrive3 = motor(PORT3, ratio6_1, true);

motor rightDrive1 = motor(PORT4, ratio6_1, true);
motor rightDrive2 = motor(PORT5, ratio6_1, false);
motor rightDrive3 = motor(PORT6, ratio6_1, false);

motor intake = motor(PORT7, ratio6_1, true);
motor catapult = motor(PORT8, ratio6_1, false);

digital_out wingLeft = digital_out(Brain.ThreeWirePort.G);
digital_out wingRight = digital_out(Brain.ThreeWirePort.H);


// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  /* calibrate the drivetrain gyro
  wait(200, msec);
  TurnGyroSmart.startCalibration(1);
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  wait(50, msec);
  Brain.Screen.clearScreen();
  */
}