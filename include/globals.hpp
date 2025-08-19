// globals.hpp
#pragma once
#include "lemlib/api.hpp"

// Declare chassis so other files can use it
extern lemlib::Chassis chassis;

extern void moveDistance(int dist, int timeout, bool async = true);
