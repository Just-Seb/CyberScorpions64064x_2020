#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
inertial Inertial = inertial(PORT9);
motor Drive1 = motor(PORT1, ratio18_1, false);
motor Drive2 = motor(PORT2, ratio18_1, false);
motor Drive3 = motor(PORT3, ratio18_1, false);
motor Drive4 = motor(PORT4, ratio18_1, false);
motor In1 = motor(PORT5, ratio18_1, false);
motor In2 = motor(PORT6, ratio18_1, false);
motor Launch1 = motor(PORT7, ratio18_1, false);
motor Launch2 = motor(PORT8, ratio18_1, false);
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