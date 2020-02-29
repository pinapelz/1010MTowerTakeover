#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "v5.h"
#include "v5_vcs.h"
#include "vex.h"

using namespace vex;
void lockWheels(){
  LeftMotorB.stop(brakeType::hold);
  LeftMotorF.stop(brakeType::hold);
  RightMotorF.stop(brakeType::hold);
  RightMotorB.stop(brakeType::hold);
}
void stackCube() {
   lockWheels();
  Lift.stop(brakeType::hold); // Stop the arm
  Pusher.setVelocity(100, velocityUnits::pct); // Set the pusher speed to 90% of max speed
  Lift.stop(brakeType::hold);  // Stop the arm
  lockWheels();
  Pusher.rotateFor(1300, rotationUnits::deg,true);     // Rotate the pusher by 375 degrees
  Lift.stop(brakeType::hold); // Stop the arm
    lockWheels();
  Pusher.setVelocity(70, velocityUnits::pct); // Set the pusher speed to 60% of the max speed
  Lift.stop(brakeType::hold);  // Stop the arm
  Pusher.rotateFor(600, rotationUnits::deg,true);   
  lockWheels();
  Pusher.setVelocity(35, velocityUnits::pct); // Set the pusher speed to 60% of the max speed
  Lift.stop(brakeType::hold);  // Stop the arm
  Pusher.rotateFor(610, rotationUnits::deg,false);   
  lockWheels();
   task::sleep(2000); //if action not completed in 2 seconds keep going
 
  /*Pusher.setVelocity(40, velocityUnits::pct); // Set the pusher speed to 60% of the max speed
  Lift.stop(brakeType::hold);  // Stop the arm
  Pusher.rotateFor(500, rotationUnits::deg,true);   
  lockWheels(); 
  Lift.stop(brakeType::hold); // Stop the arm
  Pusher.setVelocity(30, velocityUnits::pct); // Set the pusher speed to 10% of the full speed
  lockWheels();
  Lift.stop(brakeType::hold);  // Stop the arm
  Pusher.rotateFor(50, rotationUnits::deg,true);     // Rotate the pusher by 60 rotations
  Lift.stop(brakeType::hold); // Stop the arm */
}
void cubeLock(){
       Lift.setVelocity(-75,vex::velocityUnits::pct);
       Lift.rotateFor(-200, rotationUnits::deg,true);
       IntakeL.spin(directionType::fwd, 50, vex::velocityUnits::pct);
       IntakeR.spin(directionType::fwd, 50, vex::velocityUnits::pct);
       task::sleep(500);
}

void stopall(int stopTime) { // Stop all the motors for specified time
  LeftMotorF.stop(brakeType::coast);
  RightMotorF.stop(brakeType::coast);
  LeftMotorB.stop(brakeType::coast);
  RightMotorB.stop(brakeType::coast);
  IntakeR.stop(brakeType::hold);
  IntakeL.stop(brakeType::hold);
  vex::task::sleep(stopTime);
}
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
  LeftMotorB.setVelocity(speed, velocityUnits::pct);
  RightMotorF.setVelocity(speed, velocityUnits::pct);
  RightMotorB.setVelocity(-speed, velocityUnits::pct);

  LeftMotorF.rotateFor(-rotation, rotationUnits::deg, false);
  RightMotorF.rotateFor(rotation, rotationUnits::deg, false);
  LeftMotorB.rotateFor(rotation, rotationUnits::deg, false);
  RightMotorB.rotateFor(-rotation, rotationUnits::deg, false);
  vex::task::sleep(time);
  stopall(10);
}

void driveForward(int speed, int rotation, int time) { // Drive forward function that uses motor degrees
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

void driveBackward(int speed,int rotation,int time) { // Drive backward function that uses motor degrees
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

void driveLeft(int speed,int rotation,int time) { // Turn left using motor degrees

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

void intake(int time,int speed) { // Spin the intake for x amount of time and at y speed
  IntakeR.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  IntakeL.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
  vex::task::sleep(time);
  stopall(10);
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
  Lift.setVelocity(-75,vex::velocityUnits::pct);
  Lift.rotateFor(-900, rotationUnits::deg,false);
  vex::task::sleep(750); 
    Lift.setVelocity(75,vex::velocityUnits::pct);
  Lift.rotateFor(1200, rotationUnits::deg,false);
  vex::task::sleep(1100); 
   
}

void stackPartA(){
  Pusher.setVelocity(90, velocityUnits::pct);
  Pusher.rotateFor(1500, rotationUnits::deg, true);
}
void stackPartB(){
  Pusher.setVelocity(45, velocityUnits::pct);
  Pusher.rotateFor(1020, rotationUnits::deg, true);
}

void BackLeftUntil(int cm){
  bool go = true;
while(go==true){
  LeftMotorF.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); 
  LeftMotorB.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); 
  task::sleep(10);
}
}

void BackRightUntil(int cm){
  bool go = true;
while(go==true){
  RightMotorF.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); 
  RightMotorB.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); 
  task::sleep(10);

}
}

void driveForwardUntilBumper(){
  bool go = true;
  while(go==true){
  LeftMotorF.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct); 
  LeftMotorB.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct); 
  RightMotorF.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct); 
  RightMotorB.spin(vex::directionType::fwd, 75, vex::velocityUnits::pct);
  task::sleep(10);
  if(!ScoringBump.pressing()){
  go=false;
  }
  }
  stopall(10);
}
void TimeIntake(int sec){
  IntakeR.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); // Intake
  IntakeL.spin(vex::directionType::rev, 127, vex::velocityUnits::pct); // Intake
  vex::task::sleep(sec); //2700
}

/*void RedSmall(){


NOT THIS CODE 8 PT NO WORK


FORMAT FOR THE CODE:
function(speed,distance,time);

speed = goes up to 127 for maximum speed
distance = vex motor degrees (for this one use the guess and check method)
time = time in milliseconds

If you are changing the distance make sure to allocate more time for the bot to do it

  //driveRight(75,1000,1500);//Turn to face the scoring zone
flipOut();//Flipout aka Run Whatever is in the Flipout(Function)
 driveBackward(45,50,50);//drive backwards and hit the wall so that the robot is lined up 
  driveForwardSecOne(127,1000,1000);   //Drive forward and intake the 2 cubes in front
  driveForwardSecOne(50,325,600);   //Drive Backward a little bit to prepare for turning
  driveLeft(127, 600,500); //Turn left to prepare for drive backward to 2nd row
  driveBackward(127, 1100, 1200);
  stopall(10);
  driveForwardSecOne(127,1100,1100);  
  driveBackward(127,650,700);
  driveRight(80,560,750);//Turn to face the scoring zone
  stackPartA();
  driveForwardUntilBumper();
  driveForward(50, 50, 100);
  stackPartB();
  driveBackward(50, 200, 500); //Back away from the cube
}*/




//FIX THE FOLLOWING TWO CODES PLEASE
void RedOneRow(){ //YES EDIT THIS
    flipOut();//You need to change this
    driveForwardSecOne(60,1600,2000); 
    intake(1500,127);
  driveBackward(127,1100,1200);
  driveRight(80,850,750);//Turn to face the scoring zone
  strafeRight(90,-1650,1800);//IDK why but strafe right always gotta be negative to work
  driveForward(60, 350, 500); 
   strafeRight(90,-100,100); //IDK why but strafe right always gotta be negative to work
   TimeIntake(300);
  stackCube();
  driveBackward(50, 200, 5000); //Back away from the cube*/

  stopall(100000); //WARNING DO NOT REMOVE THIS
}
void BlueOneRow(){
    flipOut();//You need to change this
    driveForwardSecOne(60,1600,2000); 
    driveForwardSecOne(40,600,700); 
  driveBackward(127,1100,1200);
  driveLeft(80,850,750);//Turn to face the scoring zone
  strafeLeft(90,1650,1800);

  driveForward(60, 350, 500); 
   strafeLeft(90,100,100);
   TimeIntake(300);
  stackCube();
  driveBackward(50, 200, 500); //Back away from the cube*/

  stopall(100000); //WARNING DO NOT REMOVE THIS
}
///////////////////////////////////////////////////////////








void BlueProtected(){
  flipOut();
  driveForwardSecOne(50,700,700);
  driveRight(75,450,800);
  driveForwardSecOne(50,900,1000);
  TimeIntake(500);
  strafeRight(90,-1100,1500);//Just a weird thing but strafe right has to be negative for some reason
  driveForward(50,300,500);
  stackCube();
  driveBackward(50, 200, 500); //Back away from the cube*/
  stopall(1000000);
}
void RedProtected(){
  flipOut();
  driveForwardSecOne(50,700,700);
  driveRight(75,600,800);
  strafeLeft(90,1100,1500);//Just a weird thing but strafe right has to be negative for some reason
  driveForward(70,550,1000);
  stackCube();
  driveBackward(50, 200, 500); //Back away from the cube*/
  stopall(1000000);
}
void OnePt(){
  driveBackward(75,200,200);
  driveForward(75,200,200);
  flipOut();
}