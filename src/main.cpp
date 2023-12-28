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
  Inertial.calibrate();
  Brain.Screen.print("Calibrating Inertial");
  while(Inertial.isCalibrating()) {
    wait(25, msec);
  }
  Brain.Screen.clearScreen();

  wingLeft.set(false);
  wingRight.set(false);

  leftDrive1.setPosition(0, degrees);
  leftDrive2.setPosition(0, degrees);
  leftDrive3.setPosition(0, degrees);
  rightDrive1.setPosition(0, degrees);
  rightDrive2.setPosition(0, degrees);
  rightDrive3.setPosition(0, degrees);
  catapult.setPosition(0, degrees);
 
  intake.setVelocity(100, percent);
  catapult.setVelocity(100, percent);
  catapult.setStopping(brake);
}

// PID Settings
double kP = 0.0;
double kI = 0.0;
double kD = 0.0;

double turnkP = 0.0;
double turnkI = 0.0;
double turnkD = 0.0;

// Autonomous Settings
int desiredValue = 0;
int desiredTurnValue = 0;

int error;         // X-Axis SensorValue (Encoder) - desiredXValue : Position
int prevError = 0; // X-Axis Position 5 miliseconds or whatever many ago.
int derivative;    // errorX - prevErrorX : Speed
int totalError = 0;// totalErrorX = totalErrorX + errorX

int turnError;
int turnPrevError = 0;
int turnDerivative;
int turnTotalError = 0;

bool resetDriveSensors = false;
bool enableDrivePID = true;

int DrivePID() {

  while(enableDrivePID) {

    if (resetDriveSensors) {
      resetDriveSensors = false;

      leftDrive1.setPosition(0, degrees);
      leftDrive2.setPosition(0, degrees);
      leftDrive3.setPosition(0, degrees);
      rightDrive1.setPosition(0, degrees);
      rightDrive2.setPosition(0, degrees);
      rightDrive3.setPosition(0, degrees);
    }
    ////////////////////////////////////////////////
    /// Driving movement PID
    /////////////////////

    // Assign our destination coordinates to specific arguments 
    int leftMotorPosition = (leftDrive1.position(degrees) + leftDrive2.position(degrees) + leftDrive3.position(degrees)) / 3;
    int rightMotorPosition = (rightDrive1.position(degrees) + rightDrive2.position(degrees) + rightDrive3.position(degrees)) / 3;

    int currentPos = (leftMotorPosition + rightMotorPosition) /2;
    // Potential
    error = currentPos - desiredValue;

    // Derivative
    derivative = error - prevError;

    // Integral (Detects if going too slow or fast)
    totalError += error;

    double lateralMotorPower = (error * kP + derivative * kD + totalError * kI);

    ////////////////////////////////////////////////
    /// Turning movement PID
    /////////////////////

    int turnDifference = leftMotorPosition - rightMotorPosition;

    // Potential
    turnError = turnDifference - desiredTurnValue;

    // Derivative
    turnDerivative = turnError - turnPrevError;

    // Integral (Detects if going too slow or fast)
    turnTotalError += turnError;

    double turnMotorPower = (turnError * turnkP + turnDerivative * turnkD + turnTotalError * turnkI);

    // Input motor speed and run motors
    //leftFront.setVelocity(leftFrontV, percent);
    //rightFront.setVelocity(rightFrontV, percent);
    //leftRear.setVelocity(leftRearV, percent);
    //rightRear.setVelocity(rightRearV, percent);

    leftDrive1.spin(forward, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    rightDrive1.spin(forward, lateralMotorPower - turnMotorPower, voltageUnits::volt);
    leftDrive2.spin(forward, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    rightDrive2.spin(forward, lateralMotorPower - turnMotorPower, voltageUnits::volt);
    leftDrive3.spin(forward, lateralMotorPower + turnMotorPower, voltageUnits::volt);
    rightDrive3.spin(forward, lateralMotorPower - turnMotorPower, voltageUnits::volt);

    turnPrevError = turnError;
    prevError = error;
    wait(5, msec);
  }

  return 1;
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
  /*vex::task quirky(DrivePID);

  resetDriveSensors = true;
  desiredValue = 500;
  desiredTurnValue = 200;

  vex::task::sleep(1000);*/
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
  int holdMode = 0;
  motor_group driveL(leftDrive1, leftDrive2, leftDrive3);
  motor_group driveR(rightDrive1, rightDrive2, rightDrive3);

  while (1) {
    int velocity = -Controller1.Axis2.position(percent);
    int turn = -Controller1.Axis1.position(percent);

    driveL.setVelocity(velocity + turn, percent);
    driveR.setVelocity(velocity - turn, percent);

    driveL.spin(forward);
    driveR.spin(forward);
    
    if(Controller1.ButtonL1.pressing()) { 
      if (intakePower = 1) {
        intakePower = 0;
      } else {
        intakePower = 1;
      }
      
    } 

    if(Controller1.ButtonL2.pressing()) { 
      if (intakePower = 2) {
        intakePower = 0;
      } else {
        intakePower = 2;
      }
    } 

  switch(intakePower) {
    case 2:
      intake.spin(reverse);
      break;
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

    if(Controller1.ButtonR1.pressing()) { 
      wingPower = 1;
    } 

    if(Controller1.ButtonR2.pressing()) { 
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

    if(Controller1.ButtonX.pressing()) {
      holdMode = 1;
    }

    if(Controller1.ButtonB.pressing()) {
      holdMode = 0;
    }

    switch(holdMode) {
    case 1:
      catapult.spinToPosition(150, degrees);
      break;
    case 0:
      catapult.spinToPosition(210, degrees);
      break;
  }

  if (catapult.position(degrees) > 360) {
    catapult.setPosition(0, degrees);
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
