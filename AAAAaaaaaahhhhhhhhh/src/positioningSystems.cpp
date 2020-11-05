#include "vex.h"
#include "classes.h"

int controlCallback() {

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

int positioningCallback() {

  bob.calculateVelocity();

  return 0;

}