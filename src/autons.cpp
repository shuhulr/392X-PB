#include "autons.h"
#include "lemlib/pose.hpp"
#include "globals.hpp"
#include <vector>
#include <tuple>
#include "pros/llemu.hpp"
#include "pros/rtos.hpp" // IWYU pragma: keep
#include <cstddef> // IWYU pragma: keep


lemlib::Pose origin(0, 0, 0);

lemlib::Pose BlueRightBonusStart(16, -49, 15);



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
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    chassis.setPose(BlueRightBonusStart);
    Intake();
    pros::delay(1000);
    stopIntaking();
    pros::delay(1000);
    Intake();
    
    // chassis.moveDistance(24, 800, {.maxSpeed = 90});
    // chassis.waitUntil(22);
    // matchloader.extend();
    // chassis.moveDistance(6, 500, {}, false);
    // pros::delay(500);
    // matchloader.retract();
    // chassis.moveDistance(-10, 1000, {.forwards = false}, false);
    // chassis.moveToPose(48, -58, -180, 3000, {});
    // chassis.waitUntil(26);
    // matchloader.extend();
    // chassis.waitUntilDone();
    // moveWithVoltage(50, 50);
    // pros::delay(00);
    // moveWithVoltage(25, 25);
    // pros::delay(200);
    // moveWithVoltage(-25, -25);
    // pros::delay(200);
    // moveWithVoltage(25, 25);
    // pros::delay(400);
    // moveWithVoltage(-25, -25);
    // pros::delay(400);
    // moveWithVoltage(25, 25);
    // pros::delay(200);
    // chassis.moveToPose(48, -31.5, -180, 3000, {.forwards = false}, false);
    // IntakeBoth();
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

