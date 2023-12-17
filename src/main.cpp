/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       zacharylabib                                              */
/*    Created:      12/16/2023, 9:18:06 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  const int wheelTravel = 320;
  const int trackWidth = 320;
  const int wheelBase = 130;
  int intakePower = 0;
  int catapultPower = 0;
  int wingPower = 0;
  motor_group driveL(leftDrive1, leftDrive2, leftDrive3);
  motor_group driveR(rightDrive1, rightDrive2, rightDrive3);

  while (1) {
    int velocity = -Controller1.Axis2.position(percent);
    int turn = -Controller1.Axis1.position(percent);

    driveL.setVelocity(velocity + turn, percent);
    driveR.setVelocity(velocity - turn, percent);

    driveL.spin(forward);
    driveR.spin(forward);
    
    if(Controller1.ButtonX.pressing()) { 
      intakePower = 1;
    } 

    if(Controller1.ButtonB.pressing()) { 
      intakePower = 0;
    } 

  switch(intakePower) {
    case 1:
      intake.spin(forward);
      break;
    case 0:
      intake.stop();
      break;
    }

    if(Controller1.ButtonY.pressing()) { 
      catapultPower = 1;
    } 

    if(Controller1.ButtonA.pressing()) { 
      catapultPower = 0;
    } 

  switch(catapultPower) {
    case 1:
      catapult.spin(forward);
      break;
    case 0:
      catapult.stop();
      break;
  }

    if(Controller1.ButtonUp.pressing()) { 
      wingPower = 1;
    } 

    if(Controller1.ButtonDown.pressing()) { 
      wingPower = 0;
    }

    switch(wingPower) {
    case 1:
      wingLeft.set(true);
      wingRight.set(true);
      break;
    case 0:
      wingLeft.set(false);
      wingRight.set(false);
      break;
  }

    wait(5, msec);
}
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
