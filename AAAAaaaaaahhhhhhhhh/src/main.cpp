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

// void buttonPressed() {

//   bob.zeroInertial();

// }

int controlCallback() {
  // Define bob to keep track of values for the robot
  // Bob definition start----------------------------------------------------
  // robot bob;
  // Define current acceleration and rotation for the robot
  bob.x_accl = 0;
  bob.y_accl = 0;
  bob.z_accl = 0;
  bob.x_rot = 0;
  bob.y_rot = 0;
  bob.z_rot = 0;

  // Setting motor values for the robot
  bob.D1_value = 0;
  bob.D2_value = 0;
  bob.D3_value = 0;
  bob.D4_value = 0;

  // Initializing brake counters
  bob.D1D3Brake_counter = 0;
  bob.D2D4Brake_counter = 0;
  // Bob definition end-------------------------------------------------------

    while (1) {

        // Set motor values for forward and backward motion
        bob.D1_value = Controller1.Axis3.position();
        bob.D2_value = -Controller1.Axis3.position();
        bob.D3_value = -Controller1.Axis4.position();
        bob.D4_value = Controller1.Axis4.position();

        // Add turning into motor values
        bob.D1_value = bob.D1_value + Controller1.Axis1.position();
        bob.D2_value = bob.D2_value + Controller1.Axis1.position();
        bob.D3_value = bob.D3_value + Controller1.Axis1.position();
        bob.D4_value = bob.D4_value + Controller1.Axis1.position();

        // Set tower and gripper motor values
        bob.Tower_value = -Controller2.Axis1.position();
        bob.RGrip_value = Controller2.Axis2.position();
        bob.LGrip_value = Controller2.Axis4.position();

        // if (Controller1.ButtonB.pressed()) {

        //     bob.RGrip_value = 100;

        // };

        // Move wheels and tower motors
        bob.D1.spin(vex::directionType::fwd, bob.D1_value, vex::velocityUnits::pct);
        bob.D2.spin(vex::directionType::fwd, bob.D2_value, vex::velocityUnits::pct);
        bob.D3.spin(vex::directionType::fwd, bob.D3_value, vex::velocityUnits::pct);
        bob.D4.spin(vex::directionType::fwd, bob.D4_value, vex::velocityUnits::pct);

        bob.T1.spin(vex::directionType::fwd, bob.Tower_value, vex::velocityUnits::pct);
        bob.I1.spin(vex::directionType::fwd, bob.RGrip_value, vex::velocityUnits::pct);
        bob.I2.spin(vex::directionType::fwd, bob.LGrip_value, vex::velocityUnits::pct);

        // Brakes to apply motor brakes for a short period of time after the user stops moving the robot
        // to avoid drifting
        // Brake start---------------------------------------------------------------
        if (Controller1.Axis3.position() != 0) {

          bob.D1D3Brake_counter = 0;

        }

        if (Controller1.Axis3.position() == 0) {

          while (bob.D1D3Brake_counter <= 30) {

            bob.D1.setBrake(brakeType::brake);
            bob.D3.setBrake(brakeType::brake);

            bob.D1D3Brake_counter++;

          }

        }

        if (Controller1.Axis4.position() != 0) {

          bob.D2D4Brake_counter = 0;

        }

        if (Controller1.Axis4.position() == 0) {

          while (bob.D2D4Brake_counter <= 30) {

            bob.D2.setBrake(brakeType::brake);
            bob.D4.setBrake(brakeType::brake);

            bob.D2D4Brake_counter++;

          }

        }
        // Brake functions end--------------------------------------------------------
        bob.calculateVelocity();

        vex::task::sleep(25);
    }

  return 0;
}

void usercontrol(void) {

  // Start Tasks----------------------------------------------------------------
  task control = task(controlCallback);
  // End Tasks------------------------------------------------------------------
  
  bob.updateInertial();
  bob.calculateVelocity();

  // User control code here, inside the loop
  while (1) {

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  //   // Start Tasks----------------------------------------------------------------
  // vex::task controls(controls);
  // // End Tasks------------------------------------------------------------------

  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
      vex::task::sleep(25);
    // wait(100, msec);
  }
}