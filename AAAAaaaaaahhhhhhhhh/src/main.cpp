/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Sebastian Scurtescu                                       */
/*    Created:      Oct 2, 2020                                               */
/*    Description:  64064x's code for BOB Use this version                    */
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

    float x_offset = 0.09f;
    float y_offset = 0.09f;

    float x_vel = 0.0f;
    float y_vel = 0.0f;
    float z_vel = 0.0f;

    float x_vel_n = 0.0f;
    float y_vel_n = 0.0f;
    float z_vel_n = 0.0f;

    float x_distance = 0.0f;
    float y_distance = 0.0f;
    float z_distance = 0.0f;

    int D1_value;
    int D2_value;
    int D3_value;
    int D4_value;

    int Tower_value;
    int RGrip_value;
    int LGrip_value;

    int D1D3Brake_counter;
    int D2D4Brake_counter;

    float time_last = vex::timer::systemHighResolution();
    float average_accl;
    float accls;

    bool stationary;

  // Function to update the current values for the inertial sensor
  void updateInertial() {

    x_accl = Inertial.acceleration(axisType::xaxis);
    y_accl = Inertial.acceleration(axisType::yaxis);
    z_accl = Inertial.acceleration(axisType::zaxis);

    y_rot = Inertial.orientation(orientationType::yaw, rotationUnits::deg);

    Brain.Screen.setCursor(3, 3);
    Brain.Screen.print("Y accl: %f", y_accl);

    Brain.Screen.setCursor(4, 3);
    Brain.Screen.print("X accl: %f", x_accl);

  }

  // Function for zeroing out interial sensor on the go
  void zeroInertial() {

    x_offset = Inertial.acceleration(axisType::xaxis);
    y_offset = Inertial.acceleration(axisType::yaxis);

  }

  // Function to calculate and update our current position of the robot
  void calculateVelocity() {

    // for (int u = 0; u < len(accls); u ++) {



    // }

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

//robot bob;

void pre_auton(void) {

  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // Inertial.calibrate();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print("got here");
}

void autonomous(void) {
}

void buttonPressed() {

  bob.zeroInertial();

}

void controls(robot bob) {

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

    if (Controller1.ButtonB.pressed()) {

        bob.RGrip_value = 100;

    };

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

}

void usercontrol(void) {

  // Define bob to keep track of values for the robot
  // Bob definition start----------------------------------------------------
  robot bob;

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

  // Initilize stationary counter
  bob.stationary = true;
  // Bob definition end-------------------------------------------------------

  // Start Tasks----------------------------------------------------------------
  vex::Task controls (controls(bob));
  // End Tasks------------------------------------------------------------------

  // User control code here, inside the loop
  while (1) {

    // Deal with button presses for special functions for the controller
    if (Controller1.ButtonA.pressed()) {

    	bob.zeroInertial();
    	Controller1.Screen.setCursor(1, 1);

    }

    // // Set motor values for forward and backward motion
    // bob.D1_value = Controller1.Axis3.position();
    // bob.D2_value = -Controller1.Axis3.position();
    // bob.D3_value = -Controller1.Axis4.position();
    // bob.D4_value = Controller1.Axis4.position();
    //
    // // Add turning into motor values
    // bob.D1_value = bob.D1_value + Controller1.Axis1.position();
    // bob.D2_value = bob.D2_value + Controller1.Axis1.position();
    // bob.D3_value = bob.D3_value + Controller1.Axis1.position();
    // bob.D4_value = bob.D4_value + Controller1.Axis1.position();
    //
    // // Set tower and gripper motor values
    // bob.Tower_value = -Controller2.Axis1.position();
    // bob.RGrip_value = Controller2.Axis2.position();
    // bob.LGrip_value = Controller2.Axis4.position();
    //
    // if (Controller1.ButtonB.pressed()) {
    //
    //     bob.RGrip_value = 100;
    //
    // };
    //
    // // Move wheels and tower motors
    // bob.D1.spin(vex::directionType::fwd, bob.D1_value, vex::velocityUnits::pct);
    // bob.D2.spin(vex::directionType::fwd, bob.D2_value, vex::velocityUnits::pct);
    // bob.D3.spin(vex::directionType::fwd, bob.D3_value, vex::velocityUnits::pct);
    // bob.D4.spin(vex::directionType::fwd, bob.D4_value, vex::velocityUnits::pct);
    //
    // bob.T1.spin(vex::directionType::fwd, bob.Tower_value, vex::velocityUnits::pct);
    // bob.I1.spin(vex::directionType::fwd, bob.RGrip_value, vex::velocityUnits::pct);
    // bob.I2.spin(vex::directionType::fwd, bob.LGrip_value, vex::velocityUnits::pct);
    //
    // // Brakes to apply motor brakes for a short period of time after the user stops moving the robot
    // // to avoid drifting
    // // Brake start---------------------------------------------------------------
    // if (Controller1.Axis3.position() != 0) {
    //
    //   bob.D1D3Brake_counter = 0;
    //
    // }
    //
    // if (Controller1.Axis3.position() == 0) {
    //
    //   while (bob.D1D3Brake_counter <= 30) {
    //
    //     bob.D1.setBrake(brakeType::brake);
    //     bob.D3.setBrake(brakeType::brake);
    //
    //     bob.D1D3Brake_counter++;
    //
    //   }
    //
    // }
    //
    // if (Controller1.Axis4.position() != 0) {
    //
    //   bob.D2D4Brake_counter = 0;
    //
    // }
    //
    // if (Controller1.Axis4.position() == 0) {
    //
    //   while (bob.D2D4Brake_counter <= 30) {
    //
    //     bob.D2.setBrake(brakeType::brake);
    //     bob.D4.setBrake(brakeType::brake);
    //
    //     bob.D2D4Brake_counter++;
    //
    //   }
    //
    // }
    // // Brake functions end--------------------------------------------------------

    // Update functions start-----------------------------------------------------
    // bob.updateInertial();
    bob.calculateVelocity();
    // Update functions end-------------------------------------------------------

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
