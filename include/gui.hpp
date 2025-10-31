#pragma once

#include "main.h"
#include "pros/apix.h"
#include <vector>
#include <tuple>
#include <string>

// extern declaration for your auton list (defined elsewhere)
extern std::vector<std::tuple<std::string, void(*)()>> autons;

// Functions you want to call from main.cpp
void displayImage();
void display_auton_selector();
