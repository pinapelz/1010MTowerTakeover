/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// RightMotorB          motor         2               
// LeftMotorF           motor         7               
// RightMotorF          motor         4               
// LeftMotorB           motor         8               
// IntakeR              motor         17              
// IntakeL              motor         12              
// Pusher               motor         19              
// Lift                 motor         15              
// Controller1          controller                    
// Controller2          controller                    
// StackSwitch          limit         A               
// ScoringBump          bumper        B               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "v5.h"
#include "v5_vcs.h"
#include "vex.h"
#include "movementFunctions.h"

using namespace vex;
void stackCube();
void BlueOneRow();
void cubeLock();
void RedProtected();
void BlueOneRow();
void RedOneRow();
void RedSmall();
void BlueProtected();
void OnePt();
  /*
  Autonomus Index
  -- Select Which Auto You Want To Run Using The Number --
  1: Red Unprotected Zone
  2. Red Protected Zone
  3. Blue Unportected Zone
  4. Blue Protected Zone
  5. One Point Auto
  */


//HEY LOOK HERE THIS IS USED TO SELECT THE AUTONOMUS
//HEY LOOK HERE THIS IS USED TO SELECT THE AUTONOMUS
//HEY LOOK HERE THIS IS USED TO SELECT THE AUTONOMUS
//HEY LOOK HERE THIS IS USED TO SELECT THE AUTONOMUS
int autoNumber = 3;
//HEY LOOK HERE THIS IS USED TO SELECT THE AUTONOMUS
//HEY LOOK HERE THIS IS USED TO SELECT THE AUTONOMUS
//HEY LOOK HERE THIS IS USED TO SELECT THE AUTONOMUS
//HEY LOOK HERE THIS IS USED TO SELECT THE AUTONOMUS
//CHANGE THE INTEGER VALUE

vex::competition Competition;
void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void) {
  switch(autoNumber){
    case 1 :
      RedSmall();
      break;
    case 2:
      RedProtected();
      break;
    case 3:
      BlueOneRow();
      break;
    case 4:
      BlueProtected();
      break;
    case 5 :
      OnePt();
      break;
    
    case 6:
    RedOneRow();
    break;

    case 7:
    BlueOneRow();
    break;

    default:
      break;
  }
  RedSmall();
}
//Drive Code
void usercontrol(void) {
//Variable Initalizations
 int intakeSpeed = 127;  
int stackSpeed = 50;
int outakeSpeed = 30;
float driveSpeed = 0.8;

  while (1) {

    int Ch1 = Controller1.Axis1.value()*driveSpeed; 
    int Ch3 = Controller1.Axis3.value()*driveSpeed; 
    int Ch4 = Controller1.Axis4.value()*driveSpeed; 
    LeftMotorF.spin(directionType::fwd, Ch3 + Ch1 + Ch4,velocityUnits::pct);
    LeftMotorB.spin(vex::directionType::fwd, Ch3 + Ch1 - Ch4,vex::velocityUnits::pct);
    RightMotorB.spin(vex::directionType::fwd, Ch3 - Ch1 + Ch4,vex::velocityUnits::pct);
    RightMotorF.spin(vex::directionType::fwd, Ch3 - Ch1 - Ch4,vex::velocityUnits::pct);
    Pusher.spin(vex::directionType::fwd,Controller2.Axis3.value()/1.5,vex::velocityUnits::pct);
    //Intake Speed
    if (Controller1.ButtonL2.pressing()) {
      IntakeL.spin(directionType::rev, 127, vex::velocityUnits::pct);
      IntakeR.spin(directionType::rev, 127, vex::velocityUnits::pct);

    }
    else if(Controller1.ButtonR2.pressing()){
    IntakeL.spin(directionType::fwd, outakeSpeed, vex::velocityUnits::pct);
    IntakeR.spin(directionType::fwd, outakeSpeed, vex::velocityUnits::pct);
    }
    else{
      IntakeL.stop(brakeType::hold);
      IntakeR.stop(brakeType::hold);
    }


    //Slide Controls for Stacking
    if(Controller1.ButtonA.pressing()){
       Pusher.spin(directionType::fwd, stackSpeed, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonB.pressing()&&!StackSwitch.pressing()){
      Pusher.spin(directionType::rev, 127, vex::velocityUnits::pct);
    }
    else{
      Pusher.stop(brakeType::hold);
    }


    //Arm Controls
    if(Controller1.ButtonL1.pressing()){
      Lift.spin(directionType::rev, 127, vex::velocityUnits::pct);
    }
    else if(Controller1.ButtonR1.pressing()){
      Lift.spin(directionType::fwd, 127, vex::velocityUnits::pct);
    }
    else{
      Lift.stop(brakeType::hold);
    }
   

   //Button Controls
    if(Controller1.ButtonY.pressing()){
          LeftMotorF.spin(directionType::rev, 20,velocityUnits::pct);
    LeftMotorB.spin(vex::directionType::rev, 20,vex::velocityUnits::pct);
    RightMotorB.spin(vex::directionType::rev, 20,vex::velocityUnits::pct);
    RightMotorF.spin(vex::directionType::rev, 20,vex::velocityUnits::pct);
    task::sleep(10); 
    }
    else if(Controller1.ButtonX.pressing()){
      stackCube();
    }
    else if(Controller1.ButtonUp.pressing()){
      outakeSpeed = 127;
      Controller1.rumble("..");
    }
    else if(Controller1.ButtonDown.pressing()){
      outakeSpeed = 30;
      Controller1.rumble(".");
    }
    else if(Controller1.ButtonLeft.pressing()){
      driveSpeed = 0.1;
      stackSpeed = 15;
      Controller1.rumble(".");
    }
    else if(Controller1.ButtonRight.pressing()){
      driveSpeed = 0.8;
      stackSpeed = 50;
       Controller1.rumble("..");
    }
    else{
    
    }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }

}

int main() {
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
