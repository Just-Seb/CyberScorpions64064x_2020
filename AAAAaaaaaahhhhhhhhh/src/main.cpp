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

using namespace vex;

// A global instance of competition
competition Competition;

// Creating robot class to keep track of robot values
class robot {

  public:

    motor D1 = Drive1;
    motor D2 = Drive2;
    motor D3 = Drive3;
    motor D4 = Drive4;

    motor T1 = Tower;

    motor I1 = In1;
    motor I2 = In2;

    float x_accl;
    float y_accl;
    float z_accl;
    float x_rot;
    float y_rot;
    float z_rot;

    float x_vel;
    float y_vel;
    float z_vel;

    float x_vel_n;
    float y_vel_n;
    float z_vel_n;

    float y_offset;
    float x_offset;

    float x_distance;
    float y_distance;
    float z_distance;

    int D1_value;
    int D2_value;
    int D3_value;
    int D4_value;

    int Tower_value;
    int RGrip_value;
    int LGrip_value;

    int D1D3Brake_counter;
    int D2D4Brake_counter;

    float time_last;

    robot() {

      D1 = Drive1;
      D2 = Drive2;
      D3 = Drive3;
      D4 = Drive4;

      T1 = Tower;

      I1 = In1;
      I2 = In2;

      x_accl = 0.0f;
      y_accl = 0.0f;
      z_accl = 0.0f;
      x_rot = 0.0f;
      y_rot = 0.0f;
      z_rot = 0.0f;

      x_vel = 0.0f;
      y_vel = 0.0f;
      z_vel = 0.0f;

      x_vel_n = 0.0f;
      y_vel_n = 0.0f;
      z_vel_n = 0.0f;

      y_offset = 0.0f;
      x_offset = 0.0f;

      x_distance = 0.0f;
      y_distance = 0.0f;
      z_distance = 0.0f;

      D1_value = 0;
      D2_value = 0;
      D3_value = 0;
      D4_value = 0;

      Tower_value = 0;
      RGrip_value = 0;
      LGrip_value = 0;

      D1D3Brake_counter = 0;
      D2D4Brake_counter = 0;

      time_last = vex::timer::systemHighResolution();

    }

  // Function to update the current values for the inertial sensor
  void updateInertial() {

    x_accl = Inertial.acceleration(axisType::xaxis);
    y_accl = Inertial.acceleration(axisType::yaxis);
    z_accl = Inertial.acceleration(axisType::zaxis);

    y_rot = Inertial.orientation(orientationType::yaw, rotationUnits::deg);

    Brain.Screen.setCursor(3, 3);
    Brain.Screen.print("Y accl: ", y_accl);

    Brain.Screen.setCursor(4, 3);
    Brain.Screen.print("Z accl: ", z_accl);

  }

  // Function for zeroing out interial sensor on the go
  void zeroInertial() {

    x_offset = Inertial.acceleration(axisType::xaxis);
    y_offset = Inertial.acceleration(axisType::yaxis);

  }

  // Function to calculate and update our current position of the robot
  void calculateVelocity() {

    float time_now = vex::timer::systemHighResolution();

    float time_since_last = time_now - time_last;

    x_accl = Inertial.acceleration(axisType::xaxis);
    y_accl = Inertial.acceleration(axisType::yaxis);
    z_accl = Inertial.acceleration(axisType::zaxis);

    if (x_accl > x_offset or x_accl < -x_offset) {

      x_vel_n = x_vel;

      x_vel = x_vel + (((x_accl - x_offset) / 9.806) * (time_since_last / 10000000));

      x_distance += ((x_vel * x_vel) - x_vel_n) / (2 * (x_accl - x_offset));

    }

    if (y_accl > y_offset or y_accl < -y_offset) {

      y_vel_n = y_vel;

      y_vel = y_vel + (((y_accl - y_offset) / 9.806) * (time_since_last / 10000000));

      y_distance += ((y_vel * y_vel) - y_vel_n) / (2 * (y_accl - y_offset));

    }

    // (vsquared - vnotsqaured) / 2a = d

    // vsquared = vnotsquared + 2ad

    time_last = vex::timer::systemHighResolution();

    Brain.Screen.setCursor(5, 3);
    Brain.Screen.print("Distance X: %f", x_distance);
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Distance X: %f", x_distance);

    Brain.Screen.setCursor(6, 3);
    Brain.Screen.print("Distance Y: %f", y_distance);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("Distance Y: %f", y_distance);

    Brain.Screen.setCursor(7, 3);
    Brain.Screen.print("(x,y) coors: (%f,%f)", x_distance, y_distance);
    Controller1.Screen.setCursor(4, 1);
    Controller1.Screen.print("(x,y) coors: (%f,%f)", x_distance, y_distance);

    Brain.Screen.setCursor(8, 3);
    Brain.Screen.print("X velocity: %f", x_vel);
    Controller1.Screen.setCursor(5, 1);
    Controller1.Screen.print("X vel: %f", x_vel);

    Brain.Screen.setCursor(9, 3);
    Brain.Screen.print("Y velocity: %f", y_vel);
    Controller1.Screen.setCursor(6, 1);
    Controller1.Screen.print("Y vel: %f", y_vel);

    x_vel = 0;

  }

};

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