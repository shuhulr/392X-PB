#include "autons.h"
#include "lemlib/pose.hpp"
#include "globals.hpp"
#include <vector>
#include <tuple>
#include "pros/llemu.hpp"
#include "pros/rtos.hpp"
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
    chassis.moveDistance(24, 2000, {}, false);
    // for (int i = 0; i<1; i++) {
    //     //printf("\n 1 %f", chassis.getPose().theta);
        
    //     // // chassis.turnToHeading(i*30-1, 2000, {}, false);
    //     // chassis.moveDistance(6*pow(2, i), 2000, {}, false);
    //     chassis.moveDistance(24, 2000, {}, false);
        
    //     //pros::delay(3000);
    //     //printf("\n 2 %f", chassis.getPose().theta);
    //     pros::delay(3000);
    //     chassis.setPose(origin);
    // }
    //moveDistance(24, 4000);

}

void BlueRightBonus() {
    chassis.setPose(BlueRightBonusStart);
    // chassis.moveDistance(30, 750, {.maxSpeed = 96});
    chassis.moveToPoint(23, -18, 800, {.maxSpeed = 91.5, .minSpeed = 40, .earlyExitRange = 1});
    LoadBag();
    chassis.turnToPoint(69, 0, 700);
    chassis.moveDistance(18.5, 700, {}, false);
    pros::delay(500);
    matchloader.extend();
    pros::delay(500);
    chassis.moveDistance(-17, 700, {.forwards = false});
    matchloader.retract();
    chassis.turnToPoint(48, -48, 700, {}, false);
    chassis.moveToPoint(48, -50, 800, {});
    chassis.waitUntil(40);
    matchloader.extend();
    chassis.waitUntilDone();
    chassis.turnToPoint(46, -72, 700, {}, false);
    chassis.moveDistance(15, 700, {}, false);
    chassis.moveDistance(15, 350, {.forwards = false}, false);
    chassis.moveDistance(15, 400, {}, false);
    pros::delay(1000);
    chassis.moveDistance(-15, 700, {.forwards = false}, false);
    matchloader.retract();
    chassis.turnToHeading(0, 700, {});
    pros::delay(500);
    ScoreHigh();
    fly.move(0);
    chassis.waitUntilDone();
    chassis.moveDistance(15, 700, {}, false);
    pros::delay(300);
    fly.move(128);

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

