#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor RightMotorB = motor(PORT2, ratio18_1, true);
motor LeftMotorF = motor(PORT3, ratio18_1, false);
motor RightMotorF = motor(PORT4, ratio18_1, true);
motor LeftMotorB = motor(PORT11, ratio18_1, false);
motor IntakeR = motor(PORT17, ratio18_1, false);
motor IntakeL = motor(PORT12, ratio18_1, true);
motor Pusher = motor(PORT20, ratio18_1, false);
motor Lift = motor(PORT15, ratio36_1, false);
controller Controller1 = controller(primary);
limit Limit1 = limit(Brain.ThreeWirePort.C);
limit Limit2 = limit(Brain.ThreeWirePort.A);
controller Controller2 = controller(partner);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}