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
lemlib::Pose BlueLeftAWPStart(-16, -49, -15);



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
    pros::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(BlueRightBonusStart);
    Intake();
    chassis.moveDistance(24, 800, {.maxSpeed = 90});
    chassis.waitUntil(23);
    matchloader.extend();
    chassis.moveDistance(10, 700, {}, false);
    chassis.moveDistance(-14, 900, {.forwards = false}, false);
    matchloader.retract();
    pros::delay(250);
    chassis.moveToPose(48, -58, -180, 3000, {.maxSpeed = 100});
    chassis.waitUntil(26);
    matchloader.extend();
    chassis.waitUntilDone();
    moveWithVoltage(50, 50);
    pros::delay(400);
    moveWithVoltage(25, 25);
    pros::delay(200);
    moveWithVoltage(-25, -25);
    pros::delay(200);
    moveWithVoltage(25, 25);
    pros::delay(400);
    moveWithVoltage(-25, -25);
    pros::delay(300);
    moveWithVoltage(50, 50);
    pros::delay(750);
    chassis.moveToPose(48.5, -33, -180, 2200, {.forwards = false}, false);
    moveWithVoltage(-25, -25);
    pros::delay(500);
    IntakeBoth();
}

void BlueLeftAWP() {
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros ::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(BlueLeftAWPStart);
    Intake();
    chassis.moveDistance(24, 800, {.maxSpeed = 90});
    chassis.waitUntil(22);
    matchloader.extend();
    chassis.moveDistance(10, 700, {}, false);
    pros::delay(200);
    chassis.moveDistance(-6, 500, {.forwards = false}, false);
    pros::delay(100);
    matchloader.retract();
    // drop.retract();
    // chassis.moveToPose(-18, -18, -135, 1500, {.forwards = false}, false);
    chassis.turnToPoint(0, 0, 700, {.forwards = false}, false);
    chassis.moveDistance(-15, 700, {.forwards = false}, false);
    drop.retract();
    moveWithVoltage(-50, -50);
    pros::delay(100);
    stopDrive();
    IntakeBoth();
    pros::delay(1000);
    drop.extend();
    stopIntaking();
    chassis.moveDistance(30, 1000, {.minSpeed = 50, .earlyExitRange = 8}, false);
    chassis.moveToPose(-48,  -60, -180, 2500, {.maxSpeed = 100});
    chassis.waitUntil(26);
    matchloader.extend();
    chassis.waitUntilDone();
    Intake();

    moveWithVoltage(50, 50);
    pros::delay(400);
    moveWithVoltage(25, 25);
    pros::delay(200);
    moveWithVoltage(-25, -25);
    pros::delay(200);
    moveWithVoltage(25, 25);
    pros::delay(400);
    moveWithVoltage(-25, -25);
    pros::delay(300);
    moveWithVoltage(50, 50);
    pros::delay(750);
    chassis.moveToPose(-48.5, -33, -180, 2200, {.forwards = false}, false);
    moveWithVoltage(-25, -25);
    pros::delay(500);
    IntakeBoth();

    
}

void BlueRightAWP() {
    float startTime = pros::millis();
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(BlueRightBonusStart);
    chassis.moveDistance(24, 800, {.maxSpeed = 90});
    chassis.waitUntil(10);
    Intake();
    chassis.waitUntil(18);
    matchloader.extend();
    chassis.moveDistance(10, 700, {}, false);
    pros::delay(200);
    chassis.moveDistance(-6, 500, {.forwards = false}, false);
    pros::delay(50);
    matchloader.retract();
    // drop.retract();
    // chassis.moveToPose(-18, -18, -135, 1500, {.forwards = false}, false);
    chassis.turnToPoint(0, 0, 700, {}, false);
    chassis.moveDistance(15, 700, {}, false);
    lowFunnel.retract();
    moveWithVoltage(-50, -50);
    pros::delay(100);
    stopDrive();
    intaking = false;
    fly.move(-95);
    chassis.turnToHeading(-60, 500, {}, false);
    intake.move(-95);
    pros::delay(1500);
    stopIntaking();
    chassis.moveDistance(-18, 800, {.forwards = false}, false);
    lowFunnel.extend();
    chassis.moveToPose(48,  -60, -180, 2500, {.maxSpeed = 100, .maxAngularSpeed = 100});
    chassis.waitUntil(26);
    matchloader.extend();
    chassis.waitUntilDone();
    Intake();

    moveWithVoltage(50, 50);
    pros::delay(400);
    moveWithVoltage(25, 25);
    pros::delay(200);
    moveWithVoltage(-25, -25);
    pros::delay(200);
    moveWithVoltage(25, 25);
    pros::delay(400);
    moveWithVoltage(-25, -25);
    pros::delay(300);
    moveWithVoltage(50, 50);
    pros::delay(400);
    printf("\n\n\n\nPose before moveToPose: %f, %f, %f\n\n\n\n", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    chassis.moveToPose(48, -33, -180, 2400, {.forwards = false, .maxAngularSpeed = 10}, false);
    printf("\n\n\n\nPose after moveToPose: %f, %f, %f\n\n\n\n", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    moveWithVoltage(-30, -30);
    pros::delay(100);
    IntakeBoth();
    float endTime = pros::millis();
    float elapsed = (endTime - startTime)/1000;
    printf("\nBlueRightAWP start %f s\n", startTime);
    printf("\nBlueRightAWP ended at %f s\n", endTime);
    printf("\nBlueRightAWP took %f s\n", elapsed);
    pros::lcd::print(6, "BlueRightAWP: %f s", elapsed);
    // chassis.setPose(origin);
    // chassis.moveToPose(-24, -48, -90, 5000, {.maxSpeed = 100});
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

void randomAhhTesting() {
    lowFunnel.extend();
    drop.extend();
    odomLift.extend();
    descorer.extend();
    matchloader.extend();
}

// vector of tuple of function description and pointers
std::vector<std::tuple<std::string, void(*)()>> autons = {
    {"PID testing auto", PIDTest},
    {"Blue Right Bonus", BlueRightBonus},
    {"Blue Left AWP", BlueLeftAWP},
    {"Blue Right AWP", BlueRightAWP},
    {"skills auto", autonSkills},
    {"random testing", randomAhhTesting}
};


/*
2d arra
autions[][] = {{"auton left", autonLeft}, {"autonright short summary", autonright}}
*/

