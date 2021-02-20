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
motor D4 = motor(PORT19, ratio18_1, false);
motor In1 = motor(PORT20, ratio18_1, false);
motor T1 = motor(PORT17, ratio18_1, false);
motor L1 = motor(PORT3, ratio18_1, false);
motor L2 = motor(PORT8, ratio18_1, false);
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

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