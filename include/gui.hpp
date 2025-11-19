#pragma once

#include "main.h" // IWYU pragma: keep
#include "pros/apix.h" // IWYU pragma: keep
#include <vector>
#include <tuple>
#include <string>

// extern declaration for your auton list (defined elsewhere)
extern std::vector<std::tuple<std::string, void(*)()>> autons;

// Functions you want to call from main.cpp
void displayImage();
void display_auton_selector();
