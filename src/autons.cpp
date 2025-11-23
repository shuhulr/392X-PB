#include "autons.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "globals.hpp"
#include <vector>
#include <tuple>
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp" // IWYU pragma: keep
#include <cstddef> // IWYU pragma: keep


// auton num
int autonIndex = 0;

extern bool screenTaskRunning;


lemlib::Pose origin(0, 0, 0);

lemlib::Pose RightStandardStart(16, -49, 15);
lemlib::Pose LeftStandardStart(-16, -49, -15);
lemlib::Pose SoloStart(-10, -45, 20);
lemlib::Pose SoloSigStart(15.5, -48, 90);



void RightBonus() {
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(RightStandardStart);
    Intake();
    chassis.moveDistance(28, 1000, {.maxSpeed = 100});
    chassis.waitUntil(15);
    matchloader.extend();
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.moveDistance(-10, 400, {.forwards = false}, false);
    chassis.moveToPose(47.5, -72, -180, 2300, {.maxSpeed = 100, .minSpeed = 40}, false);
    chassis.turnToPoint(47.5, -24, 600, {.forwards = false}, false);
    // go to long goal and score
    chassis.moveToPoint(48, -32, 1000, {.forwards = false, .maxAngularSpeed = 5}, false);
    moveWithVoltage(-50, -50);
    IntakeBoth();
    pros::delay(2150);
    stopIntaking();
    chassis.moveDistance(15, 300, {}, false);
    chassis.turnToHeading(-115, 450, {}, false);
    chassis.moveDistance(-11.5, 400, {.forwards = false}, false);
    chassis.turnToHeading(179, 500, {}, false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.moveDistance(-27, 800, {.forwards = false, .maxSpeed = 110}, false);

}

void Right4BallPush() {
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(SoloSigStart);
    chassis.moveDistance(30, 700, {}, false);
    matchloader.extend();
    chassis.turnToHeading(182, 580, {}, false);
    Intake();
    moveWithVoltage(60, 60);
    pros::delay(250);
    moveWithVoltage(35, 35);
    pros::delay(470);
    chassis.turnToPoint(47.5, -24, 500, {.forwards = false}, false);
    // go to long goal and score
    chassis.moveToPoint(48, -32, 1000, {.forwards = false, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-100, -100);
    IntakeBoth();
    pros::delay(1500);
    stopIntaking();
    chassis.moveDistance(15, 300, {}, false);
    chassis.turnToHeading(-115, 450, {}, false);
    chassis.moveDistance(-11.5, 400, {.forwards = false}, false);
    chassis.turnToHeading(180, 400, {}, false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.moveDistance(-29, 800, {.forwards = false, .maxSpeed = 110}, false);
}

void RightBonus9ball() {
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(RightStandardStart);
    Intake();
    fly.move(-32);
    chassis.moveDistance(24, 800, {.maxSpeed = 85});
    chassis.waitUntil(16);
    matchloader.extend();
    chassis.moveDistance(13, 700, {}, false);
    matchloader.retract();
    pros::delay(200);
    chassis.turnToPoint(48, -3, 600, {}, false);
    chassis.moveDistance(18, 800, {.maxSpeed = 85}, false);
    matchloader.extend();
    pros::delay(300);
    chassis.moveDistance(-29, 800, {.forwards = false}, false);
    matchloader.retract();

    chassis.moveToPose(48, -64, -180, 1100, {.lead = 0.5, .maxSpeed = 100}, false);
    pros::delay(200);
    chassis.turnToPoint(48, -24, 700, {.forwards = false}, false);
    chassis.moveDistance(-25, 800, {.forwards = false}, false);
    
    moveWithVoltage(-60, -60);
    IntakeBoth();
    pros::delay(2000);
    // chassis.waitUntil(26);
    // matchloader.extend();
    // chassis.waitUntilDone();
    stopIntaking();
    matchloader.extend();
    chassis.moveToPose(48, -64, -180, 1050, {.maxSpeed = 100, .maxAngularSpeed = 10}, false);



    Intake();
    moveWithVoltage(110, 110);
    pros::delay(600);
    moveWithVoltage(-30, -30);
    pros::delay(50);
    moveWithVoltage(100, 100);
    pros::delay(100);
    chassis.moveToPose(48, -33, -180, 2000, {.forwards = false, .lead = 0.6, .maxAngularSpeed = 10}, false);
    // chassis.moveDistance(-35, 1200, {.forwards = false, .maxSpeed = 67}, false);
    moveWithVoltage(-60, -60);
    pros::delay(100);
    IntakeBoth();
}

void Left4Plus5() {
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros ::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(LeftStandardStart);
    Intake();
    fly.move(-32);
    chassis.moveDistance(24.5, 800, {.maxSpeed = 90});
    chassis.waitUntil(16);
    matchloader.extend();
    chassis.moveDistance(11, 600, {}, false);
    pros::delay(100);
    chassis.moveDistance(-6, 500, {.forwards = false}, false);
    pros::delay(100);
    //matchloader.retract();
    // drop.retract();
    // chassis.moveToPose(-18, -18, -135, 1500, {.forwards = false}, false);
    chassis.turnToPoint(0, 0, 700, {.forwards = false}, false);
    chassis.moveDistance(-20, 650, {.forwards = false});
    chassis.waitUntil(12);
    drop.retract();
    IntakeBoth();
    intaking = false;
    moveWithVoltage(-50, -50);
    pros::delay(50);
    stopDrive();
    pros::delay(1500);
    // come out of middle goal and move to 2 stack
    stopIntaking();
    Intake();
    drop.extend();
    // fly.move(-32);
    chassis.waitUntilDone();
    matchloader.retract();
    chassis.moveDistance(18, 700, {}, false);
    pros::lcd::print(0, "x: %f, y: %f, theta: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);

    // ! go to turn to 2 stack
    chassis.turnToPoint(-48, -5.5, 1000, {}, false);
    chassis.moveDistance(23.2, 1000, {}, false);
    // matchloader.extend();
    // chassis.moveDistance(5, 250, {}, false);
    matchloader.extend();
    pros::delay(25);
    float tempTheta = chassis.getPose().theta;
    chassis.turnToHeading(-90, 300, {}, false);
    chassis.turnToHeading(tempTheta, 300, {}, false);

    pros::delay(350);

    chassis.moveDistance(-27, 1600, {.forwards = false}, false);
    matchloader.retract();
    
    // move to matchloader
    chassis.moveToPose(-48, -72, -180, 2000, {.lead = 0.5, .maxSpeed = 127});
    chassis.waitUntil(16);
    matchloader.extend();
    chassis.waitUntilDone();
    moveWithVoltage(30, 30);
    pros::delay(150);
    moveWithVoltage(100, 100);
    pros::delay(250);
    pros::lcd::print(0, "x: %f, y: %f, theta: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    chassis.turnToPoint(-48.5, -24, 500, {.forwards = false}, false);
    // go to long goal and score
    chassis.moveToPoint(-48.5, -32, 1000, {.forwards = false, .maxAngularSpeed = 8}, false);
    moveWithVoltage(-100, -100);
    IntakeBoth();
    pros::delay(2200);
    stopIntaking();
    moveWithVoltage(30, 30);
    pros::delay(250);
    
    // uncomment the following /**/ */ if u want better positioning but
    // a couple unscored blocks
    /*pros::delay(1500);
    stopIntaking();
    chassis.moveDistance(15, 300, {}, false);
    chassis.turnToHeading(-115, 450, {}, false);
    chassis.moveDistance(-11.5, 400, {.forwards = false}, false);
    chassis.turnToHeading(180, 400, {}, false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.moveDistance(-29, 800, {.forwards = false, .maxSpeed = 110}, false);*/



    // chassis.turnToPoint(-48, -24, 700, {.forwards = false}, false);
    // chassis.moveDistance(-25, 800, {.forwards = false}, false);
    
    // moveWithVoltage(-60, -60);
    // IntakeBoth();
    // pros::delay(1000);
    // // chassis.waitUntil(26);
    // // matchloader.extend();
    // // chassis.waitUntilDone();
    // stopIntaking();
    // matchloader.extend();
    // chassis.moveToPose(-48, -64, -180, 1050, {.maxSpeed = 100, .maxAngularSpeed = 10}, false);



    // Intake();
    // moveWithVoltage(110, 110);
    // pros::delay(600);
    // moveWithVoltage(-30, -30);
    // pros::delay(50);
    // moveWithVoltage(100, 100);
    // pros::delay(100);
    // chassis.moveToPose(-48, -33, -180, 2000, {.forwards = false, .lead = 0.6, .maxAngularSpeed = 10}, false);
    // // chassis.moveDistance(-35, 1200, {.forwards = false, .maxSpeed = 67}, false);
    // moveWithVoltage(-60, -60);
    // pros::delay(100);
    // IntakeBoth();
}

void LeftBonus() {
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(LeftStandardStart);
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

void LeftAWPPush() {
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros ::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(LeftStandardStart);
    Intake();
    fly.move(-32);
    chassis.moveDistance(24.5, 800, {.maxSpeed = 90});
    chassis.waitUntil(18);
    matchloader.extend();
    chassis.moveDistance(10, 700, {}, false);
    pros::delay(200);
    chassis.moveDistance(-6, 500, {.forwards = false}, false);
    pros::delay(100);
    //matchloader.retract();
    // drop.retract();
    // chassis.moveToPose(-18, -18, -135, 1500, {.forwards = false}, false);
    chassis.turnToPoint(0, 0, 700, {.forwards = false}, false);
    chassis.moveDistance(-15, 700, {.forwards = false}, false);
    drop.retract();
    moveWithVoltage(-50, -50);
    pros::delay(100);
    stopDrive();
    IntakeBoth();
    pros::delay(400);
    drop.extend();
    stopIntaking();
    chassis.moveDistance(30, 1000, {.minSpeed = 50, .earlyExitRange = 8}, false);
    chassis.moveToPose(-47.5,  -56, -180, 2350, {.maxSpeed = 100});
    chassis.waitUntil(26);
    //matchloader.extend();
    Intake();
    fly.move(-32);
    chassis.waitUntilDone();

    moveWithVoltage(110, 110);
    pros::delay(600);
    moveWithVoltage(51, 51);
    pros::delay(200);

    // moveWithVoltage(-25, -25);
    // pros::delay(200);
    // moveWithVoltage(50, 50);
    // pros::delay(300);
    // moveWithVoltage(-25, -25);
    // pros::delay(200);
    // moveWithVoltage(50, 50);
    // pros::delay(400);
    chassis.moveToPose(-48.5, -33, -180, 2000, {.forwards = false, .lead = 0.5, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-90, -90);
    IntakeBoth();
    pros::delay(2000);
    stopIntaking();
    chassis.moveToPose(-35, -48, 180, 1000, {}, false);
    chassis.turnToHeading(176, 550, {}, false);
    // comment
    chassis.moveDistance(-25, 1000, {.forwards = false}, false);
}

void LeftAWP() {
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros ::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(LeftStandardStart);
    pros::delay(500);
    // DELETE TS ABOVE
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
    chassis.moveToPose(-48.5, -33, -180, 2200, {.forwards = false, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-25, -25);
    pros::delay(500);
    IntakeBoth();

    
}

void RightAWP() { // low goal
    // start: (-7.5, 47.25, 0) for new route
    float startTime = pros::millis();
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    chassis.setPose(7.5, -47.25, 0);
    chassis.moveDistance(30, 800, {.maxSpeed = 90}, false); 
    pros::delay(50);
    chassis.turnToHeading(-22.5, 400, {}, false);
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
    chassis.turnToHeading(20, 500, {}, false);
    chassis.moveDistance(-8, 500, {.forwards = false}, false);
    // move to 3 stack
    chassis.turnToPoint(24, -23, 700, {}, false);
    Intake();
    chassis.moveDistance(13, 700, {.maxSpeed = 60});
    chassis.waitUntil(8);
    matchloader.extend();
    chassis.waitUntilDone();
    pros::delay(250);
    chassis.moveToPose(48, -58, -180, 3000, {.maxSpeed = 100});
    chassis.waitUntil(26);
    matchloader.extend();
    chassis.waitUntilDone();
    moveWithVoltage(50, 50);
    pros::delay(100);
    moveWithVoltage(80, 80);
    pros::delay(700);
    chassis.moveToPose(48, -33, -180, 2200, {.forwards = false, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-25, -25);
    pros::delay(400);
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
    Intake();
    // come out of middle goal and move to match loader
    chassis.moveDistance(16, 700, {}, false);
    chassis.turnToPoint(-48, -6.5, 700, {}, false);
    chassis.moveDistance(25, 700, {}, false);
    matchloader.extend();
    intaking = false;
    pros::delay(460);
    chassis.moveDistance(-25, 700, {.forwards = false}, false);
    // matchloader.retract();
    pros::delay(150);
    // chassis.moveDistance(7, 500, {}, false);
    // pros::delay(100);
    chassis.turnToPoint(-48.5, -45, 600, {}, false);
    intaking = true;
    chassis.moveDistance(35.5, 840, {}, false);
    chassis.turnToPoint(-48.5, -70, 650, {}, false);
    chassis.moveDistance(22, 580, {}, false);

    matchloader.extend();
    moveWithVoltage(50, 50);
    pros::delay(100);
    moveWithVoltage(70, 70);
    pros::delay(450);
    // chassis.turnToHeading(180, 550, {}, false);
    stopIntaking();
    chassis.moveToPose(-48.8, -30, -180, 1800, {.forwards = false, .lead = 0.4, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-60, -60);
    pros::delay(100);
    IntakeBoth();
//     chassis.setPose(origin);
// chassis.moveToPose(-5, -28, 0, 2200, {.forwards = false, .maxAngularSpeed = 10}, false);


}

void soloSig() {
    screenTaskRunning = false;
    chassis.setPose(SoloSigStart);
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    // move to matchloader
    chassis.moveDistance(28.5, 700, {}, false);
    matchloader.extend();
    chassis.turnToHeading(182, 580, {}, false);
    Intake();
    moveWithVoltage(70, 70);
    pros::delay(250);
    moveWithVoltage(35, 35);
    pros::delay(550);
    // matchload
    chassis.turnToPoint(48, -24, 500, {.forwards = false}, false);
    // turn and move to goal
    // chassis.moveToPose(48.5, -33, -180, 1700, {.forwards = false, .lead = 0.5, .maxAngularSpeed = 10}, false);
    chassis.moveToPoint(48, -24, 740, {.forwards = false, .maxAngularSpeed = 10}, false);
    // score
    // chassis.turnToPoint(49, -24, 500, {.forwards = false}, false);
    
    // chassis.moveDistance(-30, 700, {.forwards = false}, false);
    // score
    IntakeBoth();
    moveWithVoltage(-80, -80);
    pros::delay(1500);
    matchloader.retract(); 
    // go to first 3 stack
    chassis.moveDistance(11, 500, {}, false);
    // Intake();
    fly.move(-32);
    matchloader.retract();
    // chassis.moveToPose(12, -25, -90, 1400, {.lead = 0.5, .minSpeed = 50, .earlyExitRange = 8});
    // chassis.waitUntil(24);
    // matchloader.extend();
    // chassis.waitUntilDone();
    stopIntaking();
    chassis.turnToPoint(23, -23, 550, {.forwards = true}, false);
    Intake();
    chassis.moveDistance(26.5, 800, {.minSpeed = 50, .earlyExitRange = 8.5}, false);
    matchloader.extend();
    // go to second 3 stack
    chassis.moveToPose(-24, -25, -90, 1600, {.lead = 0.4});
    chassis.waitUntil(12);
    matchloader.retract();

    // chassis.moveDistance(35, 800, {.maxSpeed = 80});
    chassis.waitUntil(45);
    
    matchloader.extend();
    
    chassis.waitUntilDone();
    chassis.turnToPoint(-5, -5, 500, {.forwards = false}, false);
    // chassis.turnToHeading(-135, 500, {}, false);
    // go to middle goal and score
    chassis.moveDistance(-19 , 650, {.forwards = false});
    chassis.waitUntil(11);
    drop.retract();
    IntakeBoth();
    intaking = false;
    moveWithVoltage(-50, -50);
    pros::delay(50);
    stopDrive();
    pros::delay(700);
    chassis.turnToPoint(-48, -48, 500, {}, false);
    // come out of middle goal and move to match loader
    // chassis.turnToPoint(-48, -48, 500, {});
    // pros::delay(150);
    stopIntaking();
    Intake();
    drop.extend();
    fly.move(-32);
    chassis.waitUntilDone();
    chassis.moveDistance(45, 1000, {}, false);
    chassis.turnToPoint(-46, -70, 500, {}, false);
    chassis.moveDistance(22, 600, {}, false);

    moveWithVoltage(60, 60);
    pros::delay(300);
    moveWithVoltage(45, 45);
    pros::delay(200);
    chassis.turnToPoint(-47.5, -24, 500, {.forwards = false}, false);
    // go to long goal and score
    chassis.moveToPoint(-48, -32, 740, {.forwards = false, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-80, -80);
    IntakeBoth();

}

void autonSkills() {
    screenTaskRunning = false;
    chassis.setPose(SoloSigStart);
    pros::Task antijamTask = pros::Task([]() { antijam(); });
    pros::Task antijamFlyTask = pros::Task([]() { antijamFly(); });
    // move to matchloader
    chassis.moveDistance(28.5, 700, {}, false);
    matchloader.extend();
    chassis.turnToHeading(182, 580, {}, false);
    Intake();
    moveWithVoltage(70, 70);
    pros::delay(250);
    moveWithVoltage(35, 35);
    pros::delay(1000);
    // matchload
    chassis.turnToPoint(48, -24, 500, {.forwards = false}, false);
    // turn and move to goal
    // chassis.moveToPose(48.5, -33, -180, 1700, {.forwards = false, .lead = 0.5, .maxAngularSpeed = 10}, false);
    chassis.moveToPoint(48, -24, 740, {.forwards = false, .maxAngularSpeed = 10}, false);
    // score
    // chassis.turnToPoint(49, -24, 500, {.forwards = false}, false);
    
    // chassis.moveDistance(-30, 700, {.forwards = false}, false);
    // score
    IntakeBoth();
    moveWithVoltage(-80, -80);
    pros::delay(5000);
    matchloader.retract(); 
    // go to first 3 stack
    chassis.moveDistance(8, 400, {}, false);
    // Intake();
    fly.move(-32);
    matchloader.retract();
    // chassis.moveToPose(12, -25, -90, 1400, {.lead = 0.5, .minSpeed = 50, .earlyExitRange = 8});
    // chassis.waitUntil(24);
    // matchloader.extend();
    // chassis.waitUntilDone();
    stopIntaking();
    chassis.turnToPoint(23, -23, 550, {.forwards = true}, false);
    Intake();
    chassis.moveDistance(25, 800, {.minSpeed = 50, .earlyExitRange = 8.5}, false);
    matchloader.extend();
    // go to second 3 stack
    chassis.moveToPose(-24, -25, -90, 1600, {.lead = 0.4});
    chassis.waitUntil(10);
    matchloader.retract();

    // chassis.moveDistance(35, 800, {.maxSpeed = 80});
    chassis.waitUntil(45);
    
    matchloader.extend();
    
    chassis.waitUntilDone();
    chassis.turnToPoint(-5, -5, 500, {.forwards = false}, false);
    // chassis.turnToHeading(-135, 500, {}, false);
    // go to middle goal and score
    chassis.moveDistance(-19 , 650, {.forwards = false});
    chassis.waitUntil(11);
    drop.retract();
    IntakeBoth();
    intaking = false;
    moveWithVoltage(-50, -50);
    pros::delay(50);
    stopDrive();
    pros::delay(5000);
    chassis.turnToPoint(-48, -48, 500, {}, false);
    // come out of middle goal and move to match loader
    // chassis.turnToPoint(-48, -48, 500, {});
    // pros::delay(150);
    stopIntaking();
    Intake();
    drop.extend();
    fly.move(-32);
    chassis.waitUntilDone();
    chassis.moveDistance(45, 1000, {}, false);
    chassis.turnToPoint(-46, -70, 500, {}, false);
    chassis.moveDistance(22, 600, {}, false);

    moveWithVoltage(80, 80);
    pros::delay(300);
    moveWithVoltage(50, 50);
    pros::delay(1000);
    chassis.turnToPoint(-47.5, -24, 500, {.forwards = false}, false);
    // go to long goal and score
    chassis.moveToPoint(-48, -32, 740, {.forwards = false, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-80, -80);
    IntakeBoth();
    pros::delay(2150);
    stopIntaking();
    chassis.moveDistance(15, 300, {}, false);
    chassis.turnToHeading(-115, 450, {}, false);
    chassis.moveDistance(-11.5, 400, {.forwards = false}, false);
    chassis.turnToHeading(179, 500, {}, false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.moveDistance(-27, 800, {.forwards = false, .maxSpeed = 110}, false);   
}

void PIDTest() {
    screenTaskRunning = true;
    chassis.setPose(origin);
    chassis.turnToHeading(5, 700, {}, false);
    pros::delay(3000);
    chassis.setPose(origin);
    chassis.turnToHeading(10, 700, {}, false);
    pros::delay(3000);
    chassis.setPose(origin);
    chassis.turnToHeading(20, 700, {}, false);
    pros::delay(3000);
    chassis.setPose(origin);
    chassis.turnToHeading(30, 700, {}, false);
    // chassis.turnToHeading(90, 700, {}, false);

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


    // chassis.moveToPose(24, 48, 0, 5000, {}, false);
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
    {"4+5 auto", Left4Plus5}, // 0
    {"Right Bonus", RightBonus}, // 1
    {"Left Bonus", LeftBonus}, // 2
    {"Left AWP", LeftAWP}, // 3
    {"Left AWP Push", LeftAWPPush}, // 4
    {"4 ball push Right)", Right4BallPush}, // 5
    {"Solo Sig AWP", soloSig}, // 6
    {"Solo AWP 7 Ball", soloAWP7ball}, // 7
    {"Half AWP", soloAWP}, // 8
    {"skills auto", autonSkills}, // 9
    {"testing auto", PIDTest} // 10
};


/*
2d arra
autions[][] = {{"auton left", autonLeft}, {"autonright short summary", autonright}}
*/

