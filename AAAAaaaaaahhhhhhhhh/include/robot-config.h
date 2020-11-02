using namespace vex;

extern brain Brain;

// VEXcode devices
extern inertial Inertial;
extern motor Drive1;
extern motor Drive2;
extern motor Drive3;
extern motor Drive4;
extern motor In1;
extern motor In2;
extern motor Tower;
extern motor Launch2;
extern controller Controller1;
extern controller Controller2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );