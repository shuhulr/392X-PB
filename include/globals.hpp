// globals.hpp
#pragma once
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"
#include "pros/adi.hpp"

// Declare chassis so other files can use it
extern lemlib::Chassis chassis;
extern lemlib::ControllerSettings linearController;
extern lemlib::ControllerSettings angularController;
extern pros::Controller controller;
extern pros::Motor intake;
extern pros::Motor fly;
extern pros::adi::Pneumatics drop;
extern pros::adi::Pneumatics matchloader;
extern pros::adi::Pneumatics descorer;
extern pros::adi::Pneumatics odomLift;

extern void turnToHeadingU30(float heading, int timeout, lemlib::TurnToHeadingParams params = {}, bool async = true);
extern void LoadBag();
extern void ScoreHigh();