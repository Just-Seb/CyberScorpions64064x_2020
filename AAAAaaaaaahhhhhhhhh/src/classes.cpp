#include "vex.h"

using namespace vex;

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