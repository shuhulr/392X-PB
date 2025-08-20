#include "autons.h"
#include "lemlib/pose.hpp"
#include "globals.hpp"
#include <vector>
#include <tuple>
#include "pros/llemu.hpp"
#include <cstddef> // IWYU pragma: keep


lemlib::Pose origin(0, 0, 0);




void PIDTest() {
    chassis.setPose(origin);
    
    // chassis.turnToHeading(chassis.getPose().theta+10, 4000);
    // chassis.turnToHeading(chassis.getPose().theta+30, 4000);
    // // chassis.turnToHeading(chassis.getPose().theta+60, 4000);
    // chassis.turnToHeading(90, 4000);
    // //printf("\n %f", chassis.getPose().theta);
    // // chassis.turnToHeading(chassis.getPose().theta+120, 4000);
    // chassis.turnToHeading(10, 4000);
    // pros::delay(1500);
    // chassis.setPose(origin);
    for (int i = 1; i<6; i++) {
        //printf("\n 1 %f", chassis.getPose().theta);
        chassis.turnToHeading(30*i, 2000, {}, false);
        //pros::delay(3000);
        //printf("\n 2 %f", chassis.getPose().theta);
        pros::delay(3000);
        chassis.setPose(origin);
    }
    // chassis.setPose(origin);
    // chassis.turnToHeading(90, 4000, {}, false);
    // pros::delay(1000);
    // chassis.setPose(origin);
    // chassis.turnToHeading(90, 4000, {}, false);
    // pros::delay(1000);
    // chassis.setPose(origin);
    // chassis.turnToHeading(90, 4000, {}, false);
    // pros::delay(1000);
    
    //moveDistance(24, 4000);

}

void autonLeft() {
    chassis.setPose(origin); // origin should be a lemlib::Pose
    
    
}

void autonRight() {
    // Another auton example
    chassis.setPose(origin);
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
    {"PID testing auto", PIDTest},
    {"left auto", autonLeft},
    {"right auto", autonRight},
    {"skills auto", autonSkills},
};


/*
2d arra
autions[][] = {{"auton left", autonLeft}, {"autonright short summary", autonright}}
*/

