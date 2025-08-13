#include "autons.h"
#include "lemlib/pose.hpp"
#include "globals.hpp"
#include <vector>
#include <tuple>
#include "pros/llemu.hpp"
#include <cstddef> // IWYU pragma: keep


lemlib::Pose origin(0, 0, 0);

// Example autonomous routines
void autonLeft() {
    chassis.setPose({0, 0, 0}); // origin should be a lemlib::Pose
    //chassis.turnToHeading(90, 5000, {}, false);
    printf("autonleft");
}

void autonRight() {
    // Another auton example
    chassis.setPose({0, 0, 0});
    printf("autonright");
    pros::lcd::print(5, "right");
}

void autonSkills() {
    chassis.setPose({0, 0, 0});
    printf("autonskills");
    pros::lcd::print(5, "skills");
}

// vector of tuple of function description and pointers
std::vector<std::tuple<std::string, void(*)()>> autons = {
    {"left auto", autonLeft},
    {"right auto", autonRight},
    {"skills auto", autonSkills},
};


/*
2d arra
autions[][] = {{"auton left", autonLeft}, {"autonright short summary", autonright}}
*/

