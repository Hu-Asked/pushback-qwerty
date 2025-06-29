#pragma once

#define PROS_USE_SIMPLE_NAMES

#include "main.h"

extern const double wheelDiameter;
extern const double gearRatio;
extern const double trackWidth;
extern const float DRIVESPEED;
extern const int TURNSPEED;

// extern PIDController pidH;
// extern PIDController pidD;

extern pros::Controller master;

extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;

extern pros::Motor m1;
extern pros::Motor m2;
extern pros::Motor m3;

extern pros::Motor m4;
extern pros::Motor m5;
extern pros::Motor m6;

extern pros::MotorGroup LeftDrive;
extern pros::MotorGroup RightDrive;

extern pros::IMU imu;

extern lemlib::Chassis chassis;