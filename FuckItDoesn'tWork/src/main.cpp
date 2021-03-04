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
// D4                   motor         20              
// G1                   motor         16              
// G2                   motor         17              
// Controller1          controller                    
// Controller2          controller                    
// ultraSensorForward   sonar         A, B            
// ultraSensorRight     sonar         C, D            
// Launcher2            motor         12              
// Launcher             motor         9               
// Vision15             vision        15              
// Inertial5            inertial      5               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
int D1_value;
int D2_value;
int D3_value;
int D4_value;
int D1D3Brake_counter;
int D2D4Brake_counter;
int Launch_Value;
float xValue;
float yValue;

int moves[11];


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();



  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

// Locking.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
//   wait(500, msec);
//   Locking.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);

//   D2.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
//   wait(500, msec);
//   D2.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);

//   D1.spin(vex::directionType::rev, -100, vex::velocityUnits::pct);
//   D3.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
//   wait(560, msec);
//   D1.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D3.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);

//   D2.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
//   wait(1700, msec);
//   D2.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);



//   D1.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
//   D3.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
//   D2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
//   wait(500, msec);
//   D1.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D3.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D2.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);

//   D1.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
//   D3.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
//   D2.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
//   wait(500, msec);
//   D1.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D3.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D2.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);

//   D1.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
//   D3.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
//   D2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
//   wait(500, msec);
//   D1.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D3.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D2.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);

//   D1.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
//   D3.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
//   D2.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
//   wait(500, msec);
//   D1.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D3.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D2.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);

//   D1.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
//   D3.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
//   D2.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
//   wait(500, msec);
//   D1.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D3.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D2.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);

//   D1.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
//   D3.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
//   D2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
//   wait(500, msec);
//   D1.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D3.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D2.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
//   D4.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);


void autonomous(void) {
  
}

void adjust() {
  xValue = xValue * cos()
}

void getControllerValues(void) {
  yValue = Controller1.Axis3.position();
  xValue = Controller1.Axis4.position();
}

void DriveThingiFunction(void) {
  getControllerValues();

  adjust();

  int turning = Controller1.Axis1.position();

  D1.spin(vex::directionType::fwd, (xValue + turning), vex::velocityUnits::pct);
  D2.spin(vex::directionType::fwd, (-yValue + turning), vex::velocityUnits::pct);
  D3.spin(vex::directionType::fwd, (-xValue + turning), vex::velocityUnits::pct);
  D4.spin(vex::directionType::fwd, (yValue + turning), vex::velocityUnits::pct);


}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // // Set motor values for forward and backward motion
    // D1_value = Controller1.Axis4.position();
    // D3_value = -Controller1.Axis4.position();
    // D2_value = -Controller1.Axis3.position();
    // D4_value = Controller1.Axis3.position();

    // // Add turning into motor values
    // D1_value = D1_value + Controller1.Axis1.position();
    // D2_value = D2_value + Controller1.Axis1.position();
    // D3_value = D3_value + Controller1.Axis1.position();
    // D4_value = D4_value + Controller1.Axis1.position();


    // // Move wheels and tower motors
    // D1.spin(vex::directionType::fwd, D1_value, vex::velocityUnits::pct);
    // D2.spin(vex::directionType::fwd, D2_value, vex::velocityUnits::pct);
    // D3.spin(vex::directionType::fwd, D3_value, vex::velocityUnits::pct);
    // D4.spin(vex::directionType::fwd, D4_value, vex::velocityUnits::pct);

    DriveThingiFunction();

    Controller1.Screen.setCursor(3, 3);
    Controller1.Screen.print(Inertial5.angle());

    if (Controller1.ButtonL1.pressing()) {
      G1.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
      G2.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
    }

    if (Controller1.ButtonL2.pressing()) {
      G1.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      G2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
    }

    if (!Controller1.ButtonL1.pressing() && !Controller1.ButtonL2.pressing()) {
      G1.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
      G2.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
    }



    if (Controller1.ButtonR1.pressing()) {
      Launcher.spin(vex::directionType::fwd, -90, vex::velocityUnits::pct);
      Launcher2.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print("somthing");
    }

    if (Controller1.ButtonR2.pressing()) {
      Launcher.spin(vex::directionType::fwd, 90, vex::velocityUnits::pct);
      Launcher2.spin(vex::directionType::fwd, -100, vex::velocityUnits::pct);
    }
    if (!Controller1.ButtonR1.pressing() && !Controller1.ButtonR2.pressing()) {
      Launcher.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
      Launcher2.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
    }

    
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
