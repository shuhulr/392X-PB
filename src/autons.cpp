#include "autons.h"
#include "lemlib/chassis/chassis.hpp"
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
lemlib::Pose SoloStart(-10, -45, 20);




void BlueRightBonus() {
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(BlueRightBonusStart);
    Intake();
    fly.move(-32);
    chassis.moveDistance(24, 800, {.maxSpeed = 85});
    chassis.waitUntil(18);
    matchloader.extend();
    chassis.moveDistance(10, 700, {}, false);
    chassis.moveDistance(-14, 900, {.forwards = false}, false);
    matchloader.retract();
    pros::delay(250);
    chassis.moveToPose(47.5, -58, -180, 3000, {.maxSpeed = 100});
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
    pros::delay(200);
    moveWithVoltage(50, 50);
    pros::delay(450);
    chassis.moveToPose(47.5, -33, -180, 2200, {.forwards = false, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-25, -25);
    pros::delay(500);
    IntakeBoth();
}

void BlueLeftBonus() {
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(BlueLeftAWPStart);
    Intake();
    fly.move(-32);
    chassis.moveDistance(24, 800, {.maxSpeed = 90});
    chassis.waitUntil(18);
    matchloader.extend();
    chassis.moveDistance(10, 700, {}, false);
    chassis.moveDistance(-14, 900, {.forwards = false}, false);
    matchloader.retract();
    pros::delay(250);
    chassis.moveToPose(-47.5, -58, -180, 3000, {.maxSpeed = 100});
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
    // moveWithVoltage(-25, -25);
    // pros::delay(200);
    // moveWithVoltage(50, 50);
    // pros::delay(450);
    chassis.moveToPose(-47.5, -33, -180, 2200, {.forwards = false, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-25, -25);
    pros::delay(500);
    IntakeBoth();
}

void BlueLeftAWP() {
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros ::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(BlueLeftAWPStart);
    Intake();
    fly.move(-32);
    chassis.moveDistance(24.5, 800, {.maxSpeed = 90});
    chassis.waitUntil(18);
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
    pros::delay(450);
    drop.extend();
    stopIntaking();
    chassis.moveDistance(30, 1000, {.minSpeed = 50, .earlyExitRange = 8}, false);
    chassis.moveToPose(-47.5,  -60, -180, 2500, {.maxSpeed = 100});
    chassis.waitUntil(26);
    matchloader.extend();
    Intake();
    fly.move(-32);
    chassis.waitUntilDone();

    moveWithVoltage(60, 60);
    pros::delay(500);
    moveWithVoltage(25, 25);
    pros::delay(100);
    moveWithVoltage(-25, -25);
    pros::delay(200);
    moveWithVoltage(50, 50);
    pros::delay(300);
    // moveWithVoltage(-25, -25);
    // pros::delay(200);
    // moveWithVoltage(50, 50);
    // pros::delay(400);
    chassis.moveToPose(-48, -33, -180, 2200, {.forwards = false, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-25, -25);
    pros::delay(500);
    IntakeBoth();

    
}

void BlueRightAWP() {
    // start: (-7.5, 47.25, 0) for new route
    float startTime = pros::millis();
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(7.5, -47.25, 0);
    chassis.moveDistance(30, 800, {.maxSpeed = 90}, false); 
    pros::delay(100);
    chassis.turnToHeading(-20, 500, {}, false);
    // drop ball in low goal
    matchloader.extend();
    pros::delay(130);
    Intake();
    intake.move(100);
    pros::delay(150);
    // come out of low goal
    matchloader.retract();
    stopIntaking();
    pros::delay(150);
    chassis.turnToHeading(0, 500, {}, false);
    chassis.moveDistance(-7, 500, {.forwards = false}, false);
    // move to 3 stack
    chassis.turnToPoint(24, -23, 700, {}, false);
    Intake();
    chassis.moveDistance(13, 700, {.maxSpeed = 60});
    chassis.waitUntil(8);
    matchloader.extend();
    chassis.waitUntilDone();
    pros::delay(250);
    chassis.moveToPose(47.5, -58, -180, 3000, {.maxSpeed = 100});
    chassis.waitUntil(26);
    matchloader.extend();
    chassis.waitUntilDone();
    moveWithVoltage(60, 60);
    pros::delay(700);
    chassis.moveToPose(47.5, -33, -180, 2200, {.forwards = false, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-25, -25);
    pros::delay(500);
    IntakeBoth();

}

void soloAWP7ball() {
    // start position and timer
    float startTime = pros::millis();
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(SoloStart);
    // move to low goal
    chassis.moveDistance(30.5, 800, {.maxSpeed = 90}, false);
    pros::delay(100);
    // drop ball in low goal
    matchloader.extend();
    pros::delay(130);
    Intake();
    pros::delay(150);
    // come out of low goal
    matchloader.retract();
    stopIntaking();
    pros::delay(150);
    chassis.moveDistance(-7, 500, {.forwards = false}, false);
    // move to 3 stack
    chassis.turnToPoint(-24, -24, 750, {}, false);
    Intake();
    chassis.moveDistance(21, 900, {.maxSpeed = 60});
    chassis.waitUntil(11);
    matchloader.extend();
    chassis.waitUntilDone();
    // turn to middle goal
    chassis.turnToPoint(0, 0, 700, {.forwards = false}, false);
    // go to middle goal and score
    chassis.moveDistance(-15, 700, {.forwards = false}, false);
    drop.retract();
    moveWithVoltage(-50, -50);
    pros::delay(100);
    stopDrive();
    IntakeBoth();
    pros::delay(450);
    drop.extend();
    stopIntaking();
    // come out of middle goal and move to match loader
    chassis.moveDistance(30, 1000, {.minSpeed = 50, .earlyExitRange = 8}, false);
    chassis.moveToPose(-47.5,  -60, -180, 2500, {.maxSpeed = 100});
    chassis.waitUntil(26);
    matchloader.extend();
    Intake();
    fly.move(-32);
    chassis.waitUntilDone();
    // matchload
    moveWithVoltage(90, 90);
    pros::delay(500);
    moveWithVoltage(-25, -25);
    pros::delay(200);
    moveWithVoltage(60, 60);
    pros::delay(300);
    // move to long goal and score
    chassis.moveToPose(-48, -33, -180, 2200, {.forwards = false, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-25, -25);
    pros::delay(500);
    IntakeBoth();
}

void soloAWP() {
    // start position and timer
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros::Task antijamFlyTask = pros::Task([]() { antijamFly(); });

    float startTime = pros::millis();
    chassis.setPose(SoloStart);
    // move to low goal
    chassis.moveDistance(31, 800, {.maxSpeed = 90}, false); 
    pros::delay(100);
    // drop ball in low goal
    matchloader.extend();
    pros::delay(130);
    Intake();
    intake.move(100);
    pros::delay(150);
    // come out of low goal
    matchloader.retract();
    stopIntaking();
    pros::delay(150);
    chassis.moveDistance(-7, 500, {.forwards = false}, false);
    // move to 3 stack
    chassis.turnToPoint(-24, -23, 700, {}, false);
    Intake();
    chassis.moveDistance(21, 880, {.maxSpeed = 60});
    chassis.waitUntil(11);
    matchloader.extend();
    chassis.waitUntilDone();
    // turn to middle goal
    chassis.turnToPoint(-0.5, 0, 800, {.forwards = false}, false);
    // go to middle goal and score
    chassis.moveDistance(-15, 700, {.forwards = false}, false);
    drop.retract();
    moveWithVoltage(-50, -50);
    pros::delay(80);
    stopDrive();
    IntakeBoth();
    matchloader.retract();
    pros::delay(400);
    drop.extend();
    stopIntaking();
    // come out of middle goal and move to match loader
    chassis.moveDistance(16, 700, {}, false);
    chassis.turnToPoint(-48, -5.5, 700, {}, false);
    chassis.moveDistance(26, 700, {}, false);
    matchloader.extend();
    Intake();
    pros::delay(500);
    chassis.moveDistance(-25, 700, {.forwards = false}, false);
    // matchloader.retract();
    pros::delay(250);
    // chassis.moveDistance(7, 500, {}, false);
    // pros::delay(100);
    chassis.turnToPoint(-48, -70, 600, {}, false);
    chassis.moveDistance(45, 900, {.maxSpeed = 80, .minSpeed = 50, .earlyExitRange = 2});
    chassis.waitUntil(15);
    matchloader.extend();
    chassis.waitUntilDone();
    moveWithVoltage(40, 60);
    pros::delay(100);
    moveWithVoltage(40, 100);
    pros::delay(700);
    stopIntaking();
    chassis.moveToPose(-48, -30, -180, 1950, {.forwards = false, .lead = 0.4, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-60, -60);
    pros::delay(100);
    IntakeBoth();
//     chassis.setPose(origin);
// chassis.moveToPose(-5, -28, 0, 2200, {.forwards = false, .maxAngularSpeed = 10}, false);


}

void autonSkills() {
    chassis.setPose({0, 0, 0});
    printf("autonskills");
    pros::lcd::print(5, "skills");
    // lowFunnel.toggle();
    chassis.moveDistance(12, 800, {.maxSpeed = 90}, false);

    
}


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

// vector of tuple of function description and pointers
std::vector<std::tuple<std::string, void(*)()>> autons = {
    {"Blue Right Bonus", BlueRightBonus},
    {"Blue Left Bonus", BlueLeftBonus},
    {"Blue Left AWP", BlueLeftAWP},
    {"Blue Right AWP", BlueRightAWP},
    {"skills auto", autonSkills},
    {" AWP", soloAWP},
    {"testing auto", PIDTest},

};


/*
2d arra
autions[][] = {{"auton left", autonLeft}, {"autonright short summary", autonright}}
*/

