/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Sebastian Scurtescu                                       */
/*    Created:      Oct 2, 2020                                               */
/*    Description:  64064x's code for BOB                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Inertial             inertial      9
// Drive1               motor         1
// Drive2               motor         2
// Drive3               motor         3
// Drive4               motor         4
// In1                  motor         5
// In2                  motor         6
// Tower                motor         7
// Launch2              motor         8
// Controller1          controller
// Controller2          controller
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "classes.h"
#include "positioningSystems.h"

using namespace vex;

// A global instance of competition
competition Competition;

robot bob;


void pre_auton(void) {

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}

void autonomous(void) {
}

void usercontrol(void) {

  // Start Tasks that run indefinitly----------------------------------------------------------------
  task control = task(controlCallback);
  // End Tasks that run indefinitly------------------------------------------------------------------

  // User control code here, inside the loop
  while (1) {

    task positioning = task(positioningCallback);

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
      vex::task::sleep(25);
    // wait(100, msec);
  }
}