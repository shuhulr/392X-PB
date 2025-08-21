// globals.hpp
#pragma once
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/chassis.hpp"

// Declare chassis so other files can use it
extern lemlib::Chassis chassis;
extern lemlib::ControllerSettings linearController;
extern lemlib::ControllerSettings angularController;

extern void moveDistance(int dist, int timeout, bool async = true);
extern void turnToHeadingU30(float heading, int timeout, lemlib::TurnToHeadingParams params = {}, bool async = true);