using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor RightMotorB;
extern motor LeftMotorF;
extern motor RightMotorF;
extern motor LeftMotorB;
extern motor IntakeR;
extern motor IntakeL;
extern motor Pusher;
extern motor Lift;
extern controller Controller1; 
extern controller Controller2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );