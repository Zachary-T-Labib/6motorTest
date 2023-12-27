using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor leftDrive1;
extern motor leftDrive2;
extern motor leftDrive3;
extern motor rightDrive1;
extern motor rightDrive2;
extern motor rightDrive3;
extern motor intake;
extern motor catapult;
extern digital_out wingLeft;
extern digital_out wingRight;
extern inertial Inertial;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);