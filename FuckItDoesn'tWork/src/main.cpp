/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// D1                   motor         18              
// D2                   motor         2               
// D3                   motor         10              
// D4                   motor         19              
// In1                  motor         20              
// T1                   motor         17              
// L1                   motor         3               
// L2                   motor         8               
// Controller1          controller                    
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

int D1_value;
int D2_value;
int D3_value;
int D4_value;
int T1_value;
int D1D3Brake_counter;
int D2D4Brake_counter;
int L1_value;
int L2_value;
int In1_value;

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // Set motor values for forward and backward motion
    D1_value = Controller1.Axis1.position();
    D3_value = -Controller1.Axis1.position();
    D2_value = -Controller1.Axis2.position();
    D4_value = Controller1.Axis2.position();

    // Add turning into motor values
    D1_value = D1_value + Controller1.Axis4.position();
    D2_value = D2_value + Controller1.Axis4.position();
    D3_value = D3_value + Controller1.Axis4.position();
    D4_value = D4_value + Controller1.Axis4.position();

    // Set tower and gripper motor values
    // T1_value = -Controller2.Axis3.position();
    // bob.RGrip_value = Controller2.Axis2.position();
    // bob.LGrip_value = Controller2.Axis4.position();

    L1_value = Controller1.Axis3.position();
    L2_value = -Controller1.Axis3.position();

    if (Controller1.ButtonL1.pressing()) {
      T1_value = 100;
    } else if (Controller1.ButtonL2.pressing()) {
      T1_value = -100;
    } else {
      T1_value = 0;
    }

    if (Controller1.ButtonR1.pressing()) {
      In1_value = 100;
    } else if (Controller1.ButtonR2.pressing()) {
      In1_value = -100;
    } else {
      In1_value = 0;
    }

    // Move wheels and tower motors
    D1.spin(vex::directionType::fwd, D1_value, vex::velocityUnits::pct);
    D2.spin(vex::directionType::fwd, D2_value, vex::velocityUnits::pct);
    D3.spin(vex::directionType::fwd, D3_value, vex::velocityUnits::pct);
    D4.spin(vex::directionType::fwd, D4_value, vex::velocityUnits::pct);

    T1.spin(vex::directionType::fwd, T1_value, vex::velocityUnits::pct);

    L1.spin(vex::directionType::fwd, L1_value, vex::velocityUnits::pct);
    L2.spin(vex::directionType::fwd, L2_value, vex::velocityUnits::pct);
    Controller1.Screen.setCursor(3, 3);
    Controller1.Screen.print(L1_value);
    Controller1.Screen.setCursor(3, 7);
    Controller1.Screen.setCursor(1, 2);
    Controller1.Screen.print(L2_value);

    In1.spin(vex::directionType::fwd, In1_value, vex::velocityUnits::pct);

    // Brakes to apply motor brakes for a short period of time after the user stops moving the robot
    // to avoid drifting
    // Brake start---------------------------------------------------------------
    if (Controller1.Axis3.position() != 0) {

      D1D3Brake_counter = 0;

    }

    if (Controller1.Axis3.position() == 0) {

      while (D1D3Brake_counter <= 30) {

        D1.setBrake(brakeType::brake);
        D3.setBrake(brakeType::brake);

        D1D3Brake_counter++;

      }

    }

    if (Controller1.Axis4.position() != 0) {

      D2D4Brake_counter = 0;

    }

    if (Controller1.Axis4.position() == 0) {

      while (D2D4Brake_counter <= 30) {

        D2.setBrake(brakeType::brake);
        D4.setBrake(brakeType::brake);

        D2D4Brake_counter++;

      }

    }
    // Brake functions end--------------------------------------------------------

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
