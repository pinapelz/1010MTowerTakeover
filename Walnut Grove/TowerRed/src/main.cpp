

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// RightMotorB          motor         2               
// LeftMotorF           motor         3               
// RightMotorF          motor         4               
// LeftMotorB           motor         11              
// IntakeR              motor         16              
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
  Pusher.setVelocity(100, velocityUnits::pct);
  Pusher.rotateFor(900, rotationUnits::deg, true);
  vex::task::sleep(100);
  Pusher.setVelocity(100, velocityUnits::pct);
  Pusher.rotateFor(-700, rotationUnits::deg, true);
  vex::task::sleep(100);
  //***********************************************************************
  // Move the arm up then down
  Lift.setVelocity(100, velocityUnits::pct);
  Lift.rotateFor(-300, rotationUnits::deg, true);
  Lift.setVelocity(100, velocityUnits::pct);
  Lift.rotateFor(400, rotationUnits::deg, true);
  //****************************************************************
  Pusher.setVelocity(100, velocityUnits::pct); // Set the pusher speed to 75
  Pusher.rotateFor(-230, rotationUnits::deg, true); // Bring the pusher back
  stopall(10);                                      // Stop all motors for 10ms

  driveBackward(75, 75); // Backward
  vex::task::sleep(300);
}
  const int cJoyDead = 8;
  const int cMotorMin = 15;
  const float cDriveExp = 1.4;
int expDrive (int joyVal, float driveExp, int joyDead, int motorMin) {
    int joySign;
    int joyMax = 127 - joyDead;
    int joyLive = abs(joyVal) - joyDead;
    if (joyVal > 0) {joySign = 1;}
    else if (joyVal < 0) {joySign = -1;}
    else {joySign = 0;}
    int power = joySign * (motorMin + ((100 - motorMin) * pow(joyLive, driveExp) / pow(joyMax, driveExp)));
    return power;
}
// EXPO drive constants


void pre_auton(void) {}

void autonomous(void) {
int driveforward = 1170;
int driveforwardspeed = 50;
   Pusher.setVelocity(100, velocityUnits::pct);
  Pusher.rotateFor(900, rotationUnits::deg, true);
  vex::task::sleep(100);
  Pusher.setVelocity(100, velocityUnits::pct);
  Pusher.rotateFor(-700, rotationUnits::deg, true);
  vex::task::sleep(100);
    Lift.setVelocity(100, velocityUnits::pct);
  Lift.rotateFor(-300, rotationUnits::deg, true);
    Lift.setVelocity(100, velocityUnits::pct);
  Lift.rotateFor(300, rotationUnits::deg, true);
  ///////////

  stopall(10); // Stop all the motors for 10 milliseconds

  //**** Move forward while intaking the four cubes
  // There are stop lines every line to hold the arm in place after every action
  LeftMotorF.setVelocity(driveforwardspeed, velocityUnits::pct);     // Set the Left Motor Forward to speed 30
  Lift.stop(vex::brakeType::hold); // Stop arm
  LeftMotorB.setVelocity(
      driveforwardspeed, velocityUnits::pct);     // Set the Left Motor Back to speed 30
  Lift.stop(vex::brakeType::hold); // Stop arm
  RightMotorF.setVelocity(
      driveforwardspeed, velocityUnits::pct);     // Set the Right Motor Forward to speed 30
  Lift.stop(vex::brakeType::hold); // Stop arm
  RightMotorB.setVelocity(
      driveforwardspeed, velocityUnits::pct);     // Set the Right Motor Back to speed 30
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
  vex::task::sleep(3200);
  //****************************Give the robot 4.35 seconds to do this task

  stopall(10); // Stop all motors for 10 milliseconds
//NEED TO CHANGE
  driveLeft(75, 1290);    // Turn right 820 motor degrees
  vex::task::sleep(1000); // Give the robot one second to do this task
  driveForward(60, 900); // Drive forward at 60 speed and 1170 motor degrees
  Lift.stop(vex::brakeType::hold); // Hold the arm in place
  vex::task::sleep(2000);          // Give the robot 2 seconds to do this
  stopall(10);                     // Stop all motors for 10ms
 // Outtake for 750 milliseconds
  stopall(10);             // Stop all motors
  driveForward(50, 220
  );    // Drive forward for 50 degrees
  vex::task::sleep(300);   // Give the robot 300 milliseconds to do this
    IntakeR.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct); 
  IntakeL.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  vex::task::sleep(150);
  placeCubes();            // Place the cubes using the function
  driveBackward(127, 200); // Back away from the cubes
  vex::task::sleep(300);   // Give the robot 300 milliseconds to do this
  // END OF AUTONOMUS
}
/*
void autonomous(void) {
int driveforward = 1170;
int driveforwardspeed = 50;
    driveForward(75,300);
    vex::task::sleep(500);
        driveBackward(75,300);
    vex::task::sleep(500);
    stopall(10);
   Pusher.setVelocity(100, velocityUnits::pct);
  Pusher.rotateFor(900, rotationUnits::deg, true);
  vex::task::sleep(100);
  Pusher.setVelocity(100, velocityUnits::pct);
  Pusher.rotateFor(-700, rotationUnits::deg, true);
  vex::task::sleep(100);
    Lift.setVelocity(100, velocityUnits::pct);
  Lift.rotateFor(-300, rotationUnits::deg, true);
    Lift.setVelocity(100, velocityUnits::pct);
  Lift.rotateFor(300, rotationUnits::deg, true);
  ///////////

  stopall(10); // Stop all the motors for 10 milliseconds

  //**** Move forward while intaking the four cubes
  // There are stop lines every line to hold the arm in place after every action
  LeftMotorF.setVelocity(driveforwardspeed, velocityUnits::pct);     // Set the Left Motor Forward to speed 30
  Lift.stop(vex::brakeType::hold); // Stop arm
  LeftMotorB.setVelocity(
      driveforwardspeed, velocityUnits::pct);     // Set the Left Motor Back to speed 30
  Lift.stop(vex::brakeType::hold); // Stop arm
  RightMotorF.setVelocity(
      driveforwardspeed, velocityUnits::pct);     // Set the Right Motor Forward to speed 30
  Lift.stop(vex::brakeType::hold); // Stop arm
  RightMotorB.setVelocity(
      driveforwardspeed, velocityUnits::pct);     // Set the Right Motor Back to speed 30
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
  vex::task::sleep(3200);
  //****************************Give the robot 4.35 seconds to do this task

  stopall(10); // Stop all motors for 10 milliseconds
//NEED TO CHANGE
  driveLeft(75, 1240);    // Turn right 820 motor degrees
  vex::task::sleep(1000); // Give the robot one second to do this task
  driveForward(60, 900); // Drive forward at 60 speed and 1170 motor degrees
  Lift.stop(vex::brakeType::hold); // Hold the arm in place
  vex::task::sleep(2000);          // Give the robot 2 seconds to do this
  stopall(10);                     // Stop all motors for 10ms
 // Outtake for 750 milliseconds
  stopall(10);             // Stop all motors
  driveForward(50, 170);    // Drive forward for 50 degrees
  vex::task::sleep(300);   // Give the robot 300 milliseconds to do this
  placeCubes();            // Place the cubes using the function
  driveBackward(127, 200); // Back away from the cubes
  vex::task::sleep(300);   // Give the robot 300 milliseconds to do this
  // END OF AUTONOMUS
}
*/
void timer1() {
 
  while (true) {

    this_thread::sleep_for(1000);
    matchTimer--;
    count++;
  }
  // A threads's callback must return an int, even though the code will never
  // get here. You must return an int here. Threads can exit, but this one does not.

}



/*********************************


Driver Control Code Below
BADGES DOWN HERE

/*********************************
*/


void usercontrol(void) {



  // Variables Used in OP Control
  int intakeSpeed = 127;
  float driveSpeed = 1;
  bool armUp = true;
  bool armDown = true;
  bool moveArm = false;
  bool timeUp = 150;
  bool movePusher = false;
  int outakeSpeed = 30;
  int aPressed = 0;
  int strafeSpeed = 127;
  thread myThread = thread(timer1);
  //thread t = thread(pushertask);
  while (1) { // While the program is running
  
  

    // Tank Drive Code
   LeftMotorF.spin(vex::directionType::fwd,Controller1.Axis3.value() / driveSpeed,vex::velocityUnits::pct);
    RightMotorF.spin(vex::directionType::fwd,
                     Controller1.Axis2.value() / driveSpeed,
                     vex::velocityUnits::pct);
    LeftMotorB.spin(vex::directionType::fwd,
                    Controller1.Axis3.value() / driveSpeed,
                    vex::velocityUnits::pct);
    RightMotorB.spin(vex::directionType::fwd,
                     Controller1.Axis2.value() / driveSpeed,
                     vex::velocityUnits::pct);
    Pusher.spin(vex::directionType::fwd,//2.3
                     Controller2.Axis3.value(),
                     vex::velocityUnits::pct);
                  
                  if(Controller2.ButtonY.pressing()){
                    placeCubes();
                  }
 if(Controller2.Axis3.value()==0&&!Controller1.ButtonA.pressing()){
   Pusher.stop(vex::brakeType::hold);
 }
  if(Controller2.ButtonL1.pressing()){
       Lift.spin(directionType::rev, 127, vex::velocityUnits::pct);
    }
     if(Controller2.ButtonR1.pressing()){
       Lift.spin(directionType::fwd, 127, vex::velocityUnits::pct);
    }
 Brain.setTimer(150,vex::timeUnits::sec);
 //ONLY USE DURING PRACTICE!!!!
 
 if(matchTimer==30){
   Controller1.rumble("--");
   Controller2.rumble("--");
     Controller1.Screen.print("30 Seconds");
  Controller2.Screen.print("30 Seconds");
 }



 //ONLY USE DURING PRACTICE!!!!

    // If L1 is pressed robot will strafe/move to the left

    // If L2 is being held down then spin the intake reverse
    if (Controller1.ButtonL2.pressing()) {
      IntakeL.spin(directionType::rev, 127, vex::velocityUnits::pct);
      IntakeR.spin(directionType::rev, 127, vex::velocityUnits::pct);
      Lift.stop(brakeType::hold);

    } 
    else if(Controller2.ButtonDown.pressing()){
      Controller1.rumble(".-.");
    }
    else if(Controller2.ButtonUp.pressing()){
flipOut();
    }
    else if(Controller2.ButtonL1.pressing()){
       Lift.spin(directionType::rev, 127, vex::velocityUnits::pct);
    }
    else if(Controller2.ButtonR1.pressing()){
       Lift.spin(directionType::fwd, 127, vex::velocityUnits::pct);
    }
    // If L1 is held down then spin the intake forward
    else if (Controller1.ButtonR2.pressing()) {
      IntakeL.spin(directionType::fwd, outakeSpeed, vex::velocityUnits::pct);
      IntakeR.spin(directionType::fwd, outakeSpeed, vex::velocityUnits::pct);

    } 
    // If Button R1 is pressed move the arm up
    else if (Controller1.ButtonL1.pressing() && armDown == true) {
      Lift.spin(directionType::rev, 127, vex::velocityUnits::pct);

      // Hopefully will be able to use Macros here
    }

    // If Button R2 is pressed move the arm down
    else if (Controller1.ButtonR1.pressing() && armUp == true) {
      Lift.spin(directionType::fwd, 127, vex::velocityUnits::pct);

      // Hopefully will be able to use Macros here
    } else if (Controller1.ButtonRight.pressing()) {
      strafeLeftDrive(strafeSpeed);

      vex::task::sleep(100); // Giving the motor time to strafe
    }

 
    else if(Controller2.ButtonUp.pressing()){
      //Preset
    }



    // If the Right Arrow is held down then make the robot move side ways
    // (right)
    else if (Controller1.ButtonLeft.pressing()) {

      strafeRightDrive(127);
      vex::task::sleep(100); // Giving the motor time to strafe
    } 
    // Push the pusher forward when A is pressed
    

    else if (Controller1.ButtonX
                 .pressing()) { // If button X is pressed on controller one then
                                // move the robot forward at 30% speed
      LeftMotorB.spin(directionType::fwd, 30, vex::velocityUnits::pct);
      RightMotorB.spin(directionType::fwd, 30, vex::velocityUnits::pct);
      LeftMotorF.spin(directionType::fwd, 30, vex::velocityUnits::pct);
      RightMotorF.spin(directionType::fwd, 30, vex::velocityUnits::pct);
      vex::task::sleep(100);
    }

    else if (Controller1.ButtonY
                 .pressing()) { // If button Y is pressed on controller one then
                                // move the robot backward at 30% speed
      LeftMotorB.spin(directionType::rev, 30, vex::velocityUnits::pct);
      RightMotorB.spin(directionType::rev, 30, vex::velocityUnits::pct);
      LeftMotorF.spin(directionType::rev, 30, vex::velocityUnits::pct);
      RightMotorF.spin(directionType::rev, 30, vex::velocityUnits::pct);
      vex::task::sleep(100);
    }

    else { // If no buttons are being pressed then stop all the motors
      IntakeL.stop();
      IntakeR.stop();
      Pusher.stop(brakeType::hold);
      Lift.stop(brakeType::hold);
     // Pusher.stop(brakeType::hold);
    }
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
