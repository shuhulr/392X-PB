// globals.hpp
#pragma once
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"

// Declare chassis so other files can use it
extern lemlib::Chassis chassis;
extern lemlib::ControllerSettings linearController;
extern lemlib::ControllerSettings angularController;
extern lemlib::ControllerSettings angularControllerU30;
extern pros::Controller controller;
extern pros::Motor intake;
extern pros::Motor fly;
extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;
extern pros::adi::Pneumatics drop;
extern pros::adi::Pneumatics matchloader;
extern pros::adi::Pneumatics descorer;
extern pros::adi::Pneumatics odomLift;
extern pros::adi::Pneumatics lowFunnel;
extern pros::Distance distanceX;
extern pros::Distance distanceY;
extern pros::Imu imu;

extern void turnToHeadingU30(float heading, int timeout, lemlib::TurnToHeadingParams params = {}, bool async = true);
extern void Intake();
extern void moveWithVoltage(int left, int right);
extern void stopIntaking();
extern void stopDrive();
extern void IntakeBoth();
extern void antijam();
extern void antijamFly();
extern lemlib::Pose distanceReset();

extern bool intaking;
extern bool flying;