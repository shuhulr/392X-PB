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
    
    // chassis.turnToHeading(90, 500);
    for (int i = 0; i<4; i++) {
        //printf("\n 1 %f", chassis.getPose().theta);
        
        // chassis.turnToHeading(i*30-1, 2000, {}, false);
        chassis.moveDistance(6*pow(2, i), 2000, {}, false);
        
        //pros::delay(3000);
        //printf("\n 2 %f", chassis.getPose().theta);
        pros::delay(3000);
        chassis.setPose(origin);
    }
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

