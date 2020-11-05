/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       classes.h                                                 */
/*    Author:       Sebastian Scurtescu                                       */
/*    Created:      Nov 5, 2020                                               */
/*    Description:  64064x's header file for classes.cpp                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

class robot {

  public:

  motor D1;
  motor D2;
  motor D3;
  motor D4;

  motor T1;

  motor I1;
  motor I2;

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

  robot();
  void updateInertial();
  void calculateVelocity();
  void zeroInertial();

};

extern robot bob;