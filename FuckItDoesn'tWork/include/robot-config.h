using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor D1;
extern motor D2;
extern motor D3;
extern motor D4;
extern motor In1;
extern motor T1;
extern motor L1;
extern motor L2;
extern controller Controller1;
extern controller Controller2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );