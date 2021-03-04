#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor D1 = motor(PORT18, ratio18_1, false);
motor D2 = motor(PORT2, ratio18_1, false);
motor D3 = motor(PORT10, ratio18_1, false);
motor D4 = motor(PORT20, ratio18_1, false);
motor G1 = motor(PORT16, ratio18_1, false);
motor G2 = motor(PORT17, ratio18_1, false);
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
sonar ultraSensorForward = sonar(Brain.ThreeWirePort.A);
sonar ultraSensorRight = sonar(Brain.ThreeWirePort.C);
motor Launcher2 = motor(PORT12, ratio18_1, false);
motor Launcher = motor(PORT9, ratio18_1, false);
/*vex-vision-config:begin*/
vision Vision15 = vision (PORT15, 50);
/*vex-vision-config:end*/
inertial Inertial5 = inertial(PORT5);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}
