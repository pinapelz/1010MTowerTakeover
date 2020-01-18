

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// RightMotorB          motor         2               
// LeftMotorF           motor         3               
// RightMotorF          motor         4               
// LeftMotorB           motor         11              
// IntakeR              motor         17              
// IntakeL              motor         12              
// Pusher               motor         20              
// Lift                 motor         15              
// Controller1          controller                    
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "v5.h"
#include "v5_vcs.h"


int count = 105; //Initalizes the time of the match. By default its set to 1 Minute 45
using namespace vex;

vex::competition Competition;


void pre_auton(void) {}//There is nothing we need to do for the pre autonomus.

//This is the thread that tracks the time for the driver. 
//The function below is only a timer the actual time checking is below in the UserControl code
void timer1() {

  while (true) {
    this_thread::sleep_for(1000);
    count--;
  
  }
}

 int intakeSpeed = 127;  
  int matchLength = 180;
  int outakeSpeed = 30;
 //Initalizes the variables that will be used during Autonomus

void usercontrol(void) {
  //Initalize the match timer which will warn the driver if time is running low on the clock
 thread matchtimer = thread(timer1);

  while (1) { //Continue running this code as long as the timer is not up

  //Get all of the controller values so we can calculate the mecanum drive code.
    int Ch1 = Controller1.Axis1.value(); //1.5
    int Ch3 = Controller1.Axis3.value(); //2
    int Ch4 = Controller1.Axis4.value(); //1.5
    int Ch2 = Controller2.Axis3.value()/1.5;
 
 //This is for optional two person driving where one preson manages the angler
     Pusher.spin(vex::directionType::fwd,Controller2.Axis3.value()/1.5,vex::velocityUnits::pct);

/**********************************************************************************************
 The Section Below is the Mecanum Code which allows to move in every direction. 
 

 Spinning Two Wheels that are diagonal to each other allow us to move in a diagonal direction

 Spinning one side of wheels towards each other and one side of the wheels away from each other
 allows us to move side to side.

 Reverse above to move in the opposite direction
************************************************************************************************/
    
    LeftMotorF.spin(directionType::fwd, Ch3 + Ch1 + Ch4,velocityUnits::pct);
    LeftMotorB.spin(vex::directionType::fwd, Ch3 + Ch1 - Ch4,vex::velocityUnits::pct);
    RightMotorB.spin(vex::directionType::fwd, Ch3 - Ch1 + Ch4,vex::velocityUnits::pct);
    RightMotorF.spin(vex::directionType::fwd, Ch3 - Ch1 - Ch4,vex::velocityUnits::pct);

                
/************************************************************************************************
/     The Code below here is all of our controlle related code (excluding the joysticks)
/     It is used to move the arm, intake, and angler
/     I will further describe the code in each if statement down below
/*************************************************************************************************\*/

      if (Controller1.ButtonR2.pressing()) {//If R2 Is pressed then outtake using the specified Outtake speed variable (127 by default)
      IntakeL.spin(directionType::fwd, outakeSpeed, vex::velocityUnits::pct);
      IntakeR.spin(directionType::fwd, outakeSpeed, vex::velocityUnits::pct);
      Lift.stop(brakeType::hold);//Hold the arm in place so that the arm doesn't bounce up and down

    }
  
    else if (Controller1.ButtonL2.pressing()) {//If L2 is being pressed down then Intake at 127 Speed (FULL POWER)
      IntakeL.spin(directionType::rev, 127, vex::velocityUnits::pct);
      IntakeR.spin(directionType::rev, 127, vex::velocityUnits::pct);

    } 
    
    if (Controller1.ButtonUp.pressing()) { //If the up arrow is pressed set the outtake speed to maximum
      outakeSpeed = 127;
    } 
    if (Controller1.ButtonDown.pressing()) {//If the down arrow is pressed set the outtake sped to 30%
      outakeSpeed = 30;
    }

     else if (Controller1.ButtonL1.pressing()) { //If L1 is pressed move the arm down
      Lift.spin(directionType::rev, 127, vex::velocityUnits::pct);

    }
  
    else if (Controller1.ButtonR1.pressing() ) {//If R1 is pressed move the arm up
      Lift.spin(directionType::fwd, 127, vex::velocityUnits::pct);
    }

     else if (Controller1.ButtonL2.pressing()) {//If L2 is pressed then Intnake at max speed
      IntakeL.spin(directionType::rev, 127, vex::velocityUnits::pct);
      IntakeR.spin(directionType::rev, 127, vex::velocityUnits::pct);
    }
   else if(Controller1.ButtonA.pressing()){//Hold A to stack at 35 Percent of max speed
     Pusher.spin(directionType::fwd, 35, vex::velocityUnits::pct);
     vex::task::sleep(10);
   }
    else if(Controller1.ButtonB.pressing()){ //Hold B to bring the angler back at max speed
     Pusher.spin(directionType::rev, 127, vex::velocityUnits::pct);
     vex::task::sleep(10);
   }
   
     else{//If nothing is being pressed then stop all the motors and hold the arm in place
      Lift.stop(brakeType::hold);//Hold the arm in place
      IntakeL.stop();
      IntakeR.stop();
      Pusher.stop(brakeType::hold);
    
    }
     /*if(count==60){//When the remaining time of the timer reaches 60 seconds then rumble the controller
       Controller1.rumble(".-.-.-.-");
       Controller1.Screen.clearScreen();
       Controller1.Screen.print("One Minute");
       //The purpose of this is to let the driver know that he is one minute away from the match being over
     }
     if(count==30){//When the remaining time of the timer reaches 60 seconds then rumble the controller
       Controller1.rumble(".-.-.-.-.-");
       Controller1.Screen.clearScreen();
       Controller1.Screen.print("30 Sec");
              //The purpose of this is to let the driver know that he is 30 seconds away from the match being over
     }
  
   */
   
    
  }
}


void stopall(int stopTime) { // Stop all the motors for specified time
  LeftMotorF.stop(brakeType::coast);
  RightMotorF.stop(brakeType::coast);
  LeftMotorB.stop(brakeType::coast);
  RightMotorB.stop(brakeType::coast);
  IntakeR.stop();
  IntakeL.stop();
  vex::task::sleep(stopTime);
}

/******************************************************************************

All of the functions below are user defined and the is meant to be called only
in the Autonomus Section.

Format: movement(speed, rotation, time given)

Speed is in Percentage
Rotation is in VEX Motor Degree units
Time is in milliseconds (this specifies the amount of time given for the robot to complete an action)

*********************************************************************************/
void strafeLeft(int speed, int rotation, int time) { // Move side ways to the left 
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  vex::task::sleep(time);
  stopall(10);
}
void strafeRight(int speed, int rotation,int time) { // Move side ways to the right
  LeftMotorF.setVelocity(-speed, velocityUnits::pct);
  LeftMotorB.setVelocity(-speed, velocityUnits::pct);
  RightMotorF.setVelocity(-speed, velocityUnits::pct);
  RightMotorB.setVelocity(-speed, velocityUnits::pct);

  LeftMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  vex::task::sleep(time);
  stopall(10);
}
void driveForward(
    int speed, int rotation, int time) { // Drive forward function that uses motor degrees
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(rotation, rotationUnits::deg, false);
  vex::task::sleep(time);
  stopall(10);
}

void placeCubes() {
  // Macro/Function used to place the cubes down with one
  // press of a button

  Lift.stop(brakeType::hold); // Stop the arm
  Pusher.setVelocity(
      90, velocityUnits::pct); // Set the pusher speed to 90% of max speed
  Lift.stop(brakeType::hold);  // Stop the arm
  Pusher.rotateFor(850, rotationUnits::deg,
                   true);     // Rotate the pusher by 375 degrees
  Lift.stop(brakeType::hold); // Stop the arm
  Pusher.setVelocity(
      60, velocityUnits::pct); // Set the pusher speed to 60% of the max speed
  Lift.stop(brakeType::hold);  // Stop the arm
  Pusher.rotateFor(375, rotationUnits::deg,
                   true);     // Rotate the pusher by another 375 degrees
  Lift.stop(brakeType::hold); // Stop the arm
  Pusher.setVelocity(
      10, velocityUnits::pct); // Set the pusher speed to 10% of the full speed
  Lift.stop(brakeType::hold);  // Stop the arm
  Pusher.rotateFor(80, rotationUnits::deg,
                   true);     // Rotate the pusher by 60 rotations
  Lift.stop(brakeType::hold); // Stop the arm
}
void driveBackward(
    int speed,
    int rotation,int time) { // Drive backward function that uses motor degrees
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  vex::task::sleep(time);
  stopall(10);
  
}
void driveRight(int speed, int rotation,int time) { // Turn right using motor degrees

  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(-rotation, rotationUnits::deg, false);
    vex::task::sleep(time);
  stopall(10);
}
void driveLeft(int speed,
               int rotation,int time) { // Turn left using motor degrees

  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(rotation, rotationUnits::deg, false);
    vex::task::sleep(time);
  stopall(10);
}

void spin(int time,
          int speed) { // Spin the intake for x amount of time and at y speed
  IntakeR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  vex::task::sleep(time);
}
void waitFor(int time){
  vex::task::sleep(time);
}
void driveForwardSecOne(int driveforwardspeed, int driveforward, int timegiven){
    LeftMotorF.setVelocity(
      driveforwardspeed,
      velocityUnits::pct);         // Set the Left Motor Forward to speed 30
  Lift.stop(vex::brakeType::hold); // Stop arm
  LeftMotorB.setVelocity(
      driveforwardspeed,
      velocityUnits::pct);         // Set the Left Motor Back to speed 30
  Lift.stop(vex::brakeType::hold); // Stop arm
  RightMotorF.setVelocity(
      driveforwardspeed,
      velocityUnits::pct);         // Set the Right Motor Forward to speed 30
  Lift.stop(vex::brakeType::hold); // Stop arm
  RightMotorB.setVelocity(
      driveforwardspeed,
      velocityUnits::pct);         // Set the Right Motor Back to speed 30
  Lift.stop(vex::brakeType::hold); // Stop arm
  LeftMotorF.rotateFor(driveforward, rotationUnits::deg,
                       false);     // Rotate motor Left Front 1300 degrees
  Lift.stop(vex::brakeType::hold); // Stop arm
  RightMotorF.rotateFor(driveforward, rotationUnits::deg,
                        false);    // Rotate the Right Front wheel 1300 degrees
  Lift.stop(vex::brakeType::hold); // Stop the arm
  LeftMotorB.rotateFor(driveforward, rotationUnits::deg,
                       false);     // Rotate the Left Back wheel 1300 degrees
  Lift.stop(vex::brakeType::hold); // Stop the arm
  RightMotorB.rotateFor(driveforward, rotationUnits::deg,
                        false); // Rotate the Right Back wheel by 1300 degrees
  IntakeR.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); // Intake
  IntakeL.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); // Intake
  Lift.stop(vex::brakeType::hold);
  vex::task::sleep(timegiven); //2700
  stopall(10);
}

void flipOut(void) { // The function we use to flip out the robot
   IntakeR.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
  vex::task::sleep(500);
}

void auton(){
/*
FORMAT FOR THE CODE:
function(speed,distance,time);

speed = goes up to 127 for maximum speed
distance = vex motor degrees (for this one use the guess and check method)
time = time in milliseconds*/


  flipOut(); //The code will only keep going after this has fully finished. Flip out the robot
  driveBackward(50,200,300);//drive backwards and hit the wall so that the robot is lined up 
  driveForwardSecOne(65,1160,2000);   //Drive forward and intake the four cubes in front
  driveLeft(75, 880, 1200); //Turn so that the intake points to the socring zone BUT is also parallel to it
  strafeRight(60,500,500);//Hit the wall by strafing 
  driveForward(50, 300, 350);//drive forward to stack in the zone
  placeCubes();  //The code will only keep going after this had finished
  driveBackward(50, 200, 500); //back away from the cubes
  
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(auton);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}