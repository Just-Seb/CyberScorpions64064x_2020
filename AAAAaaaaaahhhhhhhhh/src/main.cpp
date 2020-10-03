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
// Launch1              motor         7               
// Launch2              motor         8               
// Controller1          controller                    
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

class robot {

  public:

    motor D1;
    motor D2;
    motor D3;
    motor D4;
    
    float x_accl;
    float y_accl;
    float z_accl;
    float x_rot;
    float y_rot;
    float z_rot;

    int D1_value;
    int D2_value;
    int D3_value;
    int D4_value;

    int D1D3Brake_counter;
    int D2D4Brake_counter;

};


void pre_auton(void) {

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}

void autonomous(void) {
}

void usercontrol(void) {

  robot bob;

  bob.D1 = Drive1;
  bob.D2 = Drive2;
  bob.D3 = Drive3;
  bob.D4 = Drive4;

  bob.x_accl = 0;
  bob.y_accl = 0;
  bob.z_accl = 0;
  bob.x_rot = 0;
  bob.y_rot = 0;
  bob.z_rot = 0;
  
  bob.D1_value = 0;
  bob.D2_value = 0;
  bob.D3_value = 0;
  bob.D4_value = 0;

  bob.D1D3Brake_counter = 0;
  bob.D2D4Brake_counter = 0;

  // User control code here, inside the loop
  while (1) {
    
    bob.D1_value = Controller1.Axis3.position();
    bob.D2_value = Controller1.Axis3.position();
    bob.D3_value = -Controller1.Axis4.position();
    bob.D4_value = -Controller1.Axis4.position();

    bob.D1_value = bob.D1_value + Controller1.Axis1.position();
    bob.D2_value = bob.D2_value + Controller1.Axis1.position();
    bob.D3_value = bob.D3_value + Controller1.Axis1.position();
    bob.D4_value = bob.D4_value + Controller1.Axis1.position();

    bob.D1.spin(vex::directionType::fwd, bob.D1_value, vex::velocityUnits::pct);
    bob.D2.spin(vex::directionType::fwd, bob.D2_value, vex::velocityUnits::pct);
    bob.D3.spin(vex::directionType::fwd, bob.D3_value, vex::velocityUnits::pct);
    bob.D4.spin(vex::directionType::fwd, bob.D4_value, vex::velocityUnits::pct);

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
    wait(100, msec);
  }
}
