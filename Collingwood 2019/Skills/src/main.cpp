

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
// Limit1               limit         C               
// Limit2               limit         A               
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"
//
using namespace vex;

vex::competition Competition;
int count = 0;
int matchTimer = 105;
void strafeLeft(int speed, int rotation) { // Move side ways to the left
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(-rotation, rotationUnits::deg, false);
}
void strafeRight(int speed, int rotation) { // Move side ways to the right
  LeftMotorF.setVelocity(-speed, velocityUnits::pct);
  LeftMotorB.setVelocity(-speed, velocityUnits::pct);
  RightMotorF.setVelocity(-speed, velocityUnits::pct);
  RightMotorB.setVelocity(-speed, velocityUnits::pct);

  LeftMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(-rotation, rotationUnits::deg, false);
}
void storageFwd(int speed, int rotation) { // Move the pusher forward
  Pusher.setVelocity(speed, velocityUnits::pct);
  Pusher.rotateFor(-rotation, rotationUnits::deg, false);
}
void driveForward(
    int speed, int rotation) { // Drive forward function that uses motor degrees
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(rotation, rotationUnits::deg, false);
}
void strafeLeftDrive(int speed) { // Move sideways to the left

  LeftMotorF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  RightMotorF.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  LeftMotorB.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  RightMotorB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
}
void strafeRightDrive(int speed) { // Move side ways to the right
  LeftMotorF.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  RightMotorF.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  LeftMotorB.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
  RightMotorB.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
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
  Pusher.rotateFor(60, rotationUnits::deg,
                   true);     // Rotate the pusher by 60 rotations
  Lift.stop(brakeType::hold); // Stop the arm
}
void driveBackward(
    int speed,
    int rotation) { // Drive backward function that uses motor degrees
  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(-rotation, rotationUnits::deg, false);
}
void driveRight(int speed, int rotation) { // Turn left using motor degrees

  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(-rotation, rotationUnits::deg, false);
}
void driveLeft(int speed,
               int rotation) { // Turn left at Y speed and for X rotations

  LeftMotorF.setVelocity(speed, velocityUnits::pct);
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(speed, velocityUnits::pct);

  LeftMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(rotation, rotationUnits::deg, false);
}
void liftSpin(int speed,
              int rotation) { // Spin the arm at speed x and for y rotationUnits
  Lift.setVelocity(speed, velocityUnits::pct);
  Lift.rotateFor(rotation, rotationUnits::deg, true);
}
void spin(int time,
          int speed) { // Spin the intake for x amount of time and at y speed
  IntakeR.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
  vex::task::sleep(time);
}

void stopall(int stopTime) { // Stop all the motors for specified time
  LeftMotorF.stop();
  RightMotorF.stop();
  LeftMotorB.stop();
  RightMotorB.stop();
  IntakeR.stop();
  IntakeL.stop();
  vex::task::sleep(stopTime);
}
void flipOut(void) { // The function we use to flip out the robot
  //********Move the pusher forward and backwards so that the pusher flips out
/*Pusher.setVelocity(100, velocityUnits::pct);
  Pusher.rotateFor(900, rotationUnits::deg, true);
  vex::task::sleep(100);
  Pusher.setVelocity(100, velocityUnits::pct);
  Pusher.rotateFor(-700, rotationUnits::deg, true);
  vex::task::sleep(100);*/
  Lift.setVelocity(100, velocityUnits::pct);
  Lift.rotateFor(-300, rotationUnits::deg, true);
  Lift.setVelocity(100, velocityUnits::pct);
  Lift.rotateFor(400, rotationUnits::deg, true);
 /* Pusher.setVelocity(100, velocityUnits::pct); // Set the pusher speed to 75
  Pusher.rotateFor(-230, rotationUnits::deg, true); // Bring the pusher back*/
  
  stopall(10);                                      // Stop all motors for 10ms
  driveBackward(75, 75); // Backward
  vex::task::sleep(300);
}
const int cJoyDead = 8;
const int cMotorMin = 15;
const float cDriveExp = 1.4;
int expDrive(int joyVal, float driveExp, int joyDead, int motorMin) {
  int joySign;
  int joyMax = 127 - joyDead;
  int joyLive = abs(joyVal) - joyDead;
  if (joyVal > 0) {
    joySign = 1;
  } else if (joyVal < 0) {
    joySign = -1;
  } else {
    joySign = 0;
  }
  int power = joySign * (motorMin + ((100 - motorMin) * pow(joyLive, driveExp) /
                                     pow(joyMax, driveExp)));
  return power;
}
// EXPO drive constants
void autonomusA() {
  int driveforward = 1170;
  int driveforwardspeed = 40;
  Pusher.setVelocity(100, velocityUnits::pct);
  Pusher.rotateFor(1000, rotationUnits::deg, true);
  vex::task::sleep(100);
  Pusher.setVelocity(100, velocityUnits::pct);
  Pusher.rotateFor(-1000, rotationUnits::deg, true);
  vex::task::sleep(100);
  Lift.setVelocity(100, velocityUnits::pct);
  Lift.rotateFor(-300, rotationUnits::deg, true);
  Lift.setVelocity(100, velocityUnits::pct);
  Lift.rotateFor(280, rotationUnits::deg, true);
  driveBackward(75,500);
  vex::task::sleep(3000);
driveForward(75,500);
vex::task::sleep(3000);
}
void pidIntake(int desire){
    LeftMotorB.resetRotation();
  int kP = 100;
  int kI = 100000;
  int kD = 10000;
  int want = desire;
  int totalError = 0;
  bool done = false;
  double lastError = LeftMotorB.rotation(vex::rotationUnits::deg);
  while(done=false){
    int curr = LeftMotorB.rotation(vex::rotationUnits::deg);
    int currError = curr- want;
    totalError += currError;
    int diff = currError - lastError;
    int currSpeed = currError/kP+totalError/kI + diff/kD;
    LeftMotorB.spin(directionType::fwd, currSpeed, vex::velocityUnits::pct);
    LeftMotorF.spin(directionType::fwd, currSpeed, vex::velocityUnits::pct);
    RightMotorB.spin(directionType::fwd, currSpeed, vex::velocityUnits::pct);
    RightMotorF.spin(directionType::fwd, currSpeed, vex::velocityUnits::pct);
    IntakeR.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); // Intake
    IntakeL.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); // Intake
    lastError = currError;
    if(currError==0){
      done = true;
    }
    vex::task::sleep(20);
  }
}
void autoB(){
  flipOut();
  pidIntake(100);
}

void pre_auton(void) {}

void autonomous(void) {
  int driveforward = 1170;
  int driveforwardspeed = 40;
  Pusher.setVelocity(127, velocityUnits::pct);
  Pusher.rotateFor(1000, rotationUnits::deg, true);
  vex::task::sleep(100);
  Pusher.setVelocity(127, velocityUnits::pct);
  Pusher.rotateFor(-1000, rotationUnits::deg, true);
  vex::task::sleep(100);
  Lift.setVelocity(127, velocityUnits::pct);
  Lift.rotateFor(-300, rotationUnits::deg, true);
  Lift.setVelocity(127, velocityUnits::pct);
  Lift.rotateFor(280, rotationUnits::deg, true);

}

void timer1() {

  while (true) {
    this_thread::sleep_for(1000);
    count++;
  }
}

/*********************************


Driver Control Code Below
BADGES DOWN HERE

/*********************************
*/ int intakeSpeed = 127;
  

  int outakeSpeed = 30;
 

void usercontrol(void) {

  // Variables Used in OP Control
 
  thread myThread = thread(timer1);
 Pusher.setVelocity(100, velocityUnits::pct);
  Pusher.rotateFor(1000, rotationUnits::deg, true);
  vex::task::sleep(100);
  Pusher.setVelocity(100, velocityUnits::pct);
  Pusher.rotateFor(-1000, rotationUnits::deg, true);
  vex::task::sleep(100);
  Lift.setVelocity(100, velocityUnits::pct);
  Lift.rotateFor(-300, rotationUnits::deg, true);
  Lift.setVelocity(100, velocityUnits::pct);
  Lift.rotateFor(280, rotationUnits::deg, true);
  while (1) { // While the program is running
       int Ch1 = Controller1.Axis1.value() / 1.5;
    int Ch3 = Controller1.Axis3.value() / 2;
    int Ch4 = Controller1.Axis4.value() / 1.5;
    int Ch2 = Controller2.Axis3.value()/1.5;
 
     Pusher.spin(vex::directionType::fwd,
                     Controller2.Axis3.value(),
                     vex::velocityUnits::pct);
        LeftMotorF.spin(vex::directionType::fwd, Ch3 + Ch1 + Ch4,
                    vex::velocityUnits::pct);
    LeftMotorB.spin(vex::directionType::fwd, Ch3 + Ch1 - Ch4,
                    vex::velocityUnits::pct);
    RightMotorB.spin(vex::directionType::fwd, Ch3 - Ch1 + Ch4,
                     vex::velocityUnits::pct);
    RightMotorF.spin(vex::directionType::fwd, Ch3 - Ch1 - Ch4,
                     vex::velocityUnits::pct);

                

      if (Controller1.ButtonR2.pressing()) {
      IntakeL.spin(directionType::fwd, outakeSpeed, vex::velocityUnits::pct);
      IntakeR.spin(directionType::fwd, outakeSpeed, vex::velocityUnits::pct);
      Lift.stop(brakeType::hold);

    }
  
    

    // If L1 is held down then spin the intake forward
    else if (Controller1.ButtonL2.pressing()) {
      IntakeL.spin(directionType::rev, 127, vex::velocityUnits::pct);
      IntakeR.spin(directionType::rev, 127, vex::velocityUnits::pct);

    } 
    
     if (Controller1.ButtonUp.pressing()) {
      outakeSpeed = 127;
    } 
    if (Controller1.ButtonDown.pressing()) {
      outakeSpeed = 30;
    }

    // If Button R1 is pressed move the arm up
     else if (Controller1.ButtonL1.pressing()) {
      Lift.spin(directionType::rev, 127, vex::velocityUnits::pct);

      // Hopefully will be able to use Macros here
    }
   

    // If Button R2 is pressed move the arm down
    else if (Controller1.ButtonR1.pressing() ) {
      Lift.spin(directionType::fwd, 127, vex::velocityUnits::pct);

      // Hopefully will be able to use Macros here
    }
       else if (Controller2.ButtonL1.pressing()) {
      Lift.spin(directionType::rev, 127, vex::velocityUnits::pct);

      // Hopefully will be able to use Macros here
    }
   

    // If Button R2 is pressed move the arm down
    else if (Controller2.ButtonR1.pressing() ) {
      Lift.spin(directionType::fwd, 127, vex::velocityUnits::pct);

      // Hopefully will be able to use Macros here
    }
     else if (Controller1.ButtonL2.pressing()) {
      IntakeL.spin(directionType::rev, 127, vex::velocityUnits::pct);
      IntakeR.spin(directionType::rev, 127, vex::velocityUnits::pct);

      // Hopefully will be able to use Macros here
    }
   else if(Controller1.ButtonA.pressing()){
     Pusher.spin(directionType::fwd, 45, vex::velocityUnits::pct);
     vex::task::sleep(10);
   }
    else if(Controller1.ButtonB.pressing()){
     Pusher.spin(directionType::rev, 127, vex::velocityUnits::pct);
     vex::task::sleep(10);
   }


    // If Button R2 is pressed move the arm down
    else if (Controller1.ButtonR2.pressing()) {
           IntakeL.spin(directionType::fwd, outakeSpeed, vex::velocityUnits::pct);
      IntakeR.spin(directionType::fwd, outakeSpeed, vex::velocityUnits::pct);

      // Hopefully will be able to use Macros here
    }
   
     else{
      Lift.stop(brakeType::hold);
      IntakeL.stop();
      IntakeR.stop();
    
    }
    if(Controller2.Axis3.value()==0){
      Pusher.stop(brakeType::hold);
    }
   
    
    
        
    // Push the pusher forward when A is pressed
   
   
    
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
