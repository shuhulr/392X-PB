#include "autons.h"
#include "lemlib/pose.hpp"
#include "globals.hpp"
#include <vector>
#include "pros/llemu.hpp"
#include <cstddef> // IWYU pragma: keep


lemlib::Pose origin(0, 0, 0);

// Example autonomous routines
void autonLeft() {
    chassis.setPose({0, 0, 0}); // origin should be a lemlib::Pose
    //chassis.turnToHeading(90, 5000, {}, false);
    printf("autonleft");
    pros::lcd::print(4, "left");
}

void autonRight() {
    // Another auton example
    chassis.setPose({0, 0, 0});
    printf("autonright");
    pros::lcd::print(4, "right");
}

void autonSkills() {
    chassis.setPose({0, 0, 0});
    printf("autonskills");
    pros::lcd::print(4, "skills");
}

// Array of function pointers
std::vector<void(*)()> autons = {
    autonLeft,
    autonRight,
    autonSkills
};


void runAuton(int autonNumber) {
    if (autonNumber >= 0 && autonNumber < (sizeof(autons) / sizeof(autons[0]))) {
        autons[autonNumber]();
    } else {
        pros::lcd::set_text(0, "Invalid auton number!");
    }
}

/*
2d arra
autions[][] = {{"auton left", autonLeft}, {"autonright", autonright}}
*/

