#include "autons.h"
#include "lemlib/pose.hpp"
#include "globals.hpp"
#include <vector>
#include <tuple>
#include "pros/llemu.hpp"
#include "pros/rtos.hpp" // IWYU pragma: keep
#include <cstddef> // IWYU pragma: keep


lemlib::Pose origin(0, 0, 0);

lemlib::Pose BlueRightBonusStart(17, -53, 8.5);



void PIDTest() {
    chassis.setPose(origin);
    
    // chassis.turnToHeading(30, 700, {}, false);
    // pros::delay(3000);
    // chassis.setPose(origin);
    // chassis.turnToHeading(60, 700, {}, false);
    // pros::delay(3000);
    // chassis.setPose(origin);
    // chassis.turnToHeading(90, 700, {}, false);
    // pros::delay(3000);
    // chassis.setPose(origin);
    // chassis.turnToHeading(135, 700, {}, false);
    // pros::delay(3000);
    // chassis.setPose(origin);
    // chassis.turnToHeading(179, 700, {}, false);
    chassis.moveToPose(24, 48, 0, 5000, {}, false);
    // for (int i = 0; i<4; i++) {
    //     //printf("\n 1 %f", chassis.getPose().theta);
        
    //     // // chassis.turnToHeading(i*30-1, 2000, {}, false);
    //     chassis.moveDistance(6*pow(2, i), 1000, {}, false);
    //     // chassis.moveDistance(24, 2000, {}, false);
        
    //     //pros::delay(3000);
    //     //printf("\n 2 %f", chassis.getPose().theta);
    //     pros::delay(3000);
    //     chassis.setPose(origin);
    // }
    //moveDistance(24, 4000);

}

void BlueRightBonus() {
    chassis.setPose(BlueRightBonusStart);
    chassis.moveDistance(24, 800, {.maxSpeed = 90}, false);

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
    {"Blue Right Bonus", BlueRightBonus},
    {"right auto", autonRight},
    {"skills auto", autonSkills},
};


/*
2d arra
autions[][] = {{"auton left", autonLeft}, {"autonright short summary", autonright}}
*/

