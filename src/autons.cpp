#include "autons.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "globals.hpp"
#include <array> // IWYU pragma: keep
#include <cstdio>
#include <vector>
#include <tuple>
#include "lemlib/util.hpp"
#include "liblvgl/llemu.hpp" // IWYU pragma: keep
#include "pros/llemu.hpp" // IWYU pragma: keep
#include "pros/motors.h" // IWYU pragma: keep
#include "pros/rtos.hpp" // IWYU pragma: keep
#include <cstddef> // IWYU pragma: keep


// auton 
int auton = 9;
extern bool screenTaskRunning;


lemlib::Pose origin(0, 0, 0);

lemlib::Pose RightStandardStart(17.3, -48.6, 14);
lemlib::Pose LeftStandardStart(-17.3, -48.6, -14);
lemlib::Pose leftAWPStart(-17.7, -48.7, -90);
lemlib::Pose rightAWPStart(17, -48.7, 90);
lemlib::Pose SoloStart(-10, -45, 20);
lemlib::Pose SoloSigStart(7.4, -47.5, -90);

void rightBonus() {
    chassis.setPose(RightStandardStart);
    Intake();
    drop.extend();
    chassis.moveDistance(18, 800, {.minSpeed = 35, .earlyExitRange = 5}, false);
    moveWithVoltage(50, 25);
    pros::delay(450);
    matchloader.extend();
    pros::delay(150);
    // chassis.moveDistance(-5, 500, {.forwards = false}, false);
    // chassis.moveToPose(48, -72, 180, 2500, {.lead = 0.5, .maxSpeed = 80, .minSpeed = 45}, false);
    chassis.turnToPoint(48, -47, 500, {}, false);
    chassis.moveToPoint(48, -47, 900, {.maxSpeed = 90, .maxAngularSpeed = 10}, false);
    // pros::lcd::print(2, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);

    // pros::delay(250);
    // pros::lcd::print(3, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);

    double x = distanceResetX(false, 0);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);

    chassis.turnToPoint(48.5, -72, 500, {}, false);

    moveWithVoltage(60, 60);
    pros::delay(450);
    moveWithVoltage(40, 40);
    pros::delay(420);

    chassis.turnToPoint(48.5, -24, 500, {.forwards = false}, false);

    shotgun.move(-64);
    pros::lcd::print(1, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    chassis.moveToPoint(48, -27, 700, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-40, -40);
    shotgun.move_velocity(70);
    pros::delay(600);
    stopIntaking();

    //push
    chassis.turnToHeading(135, 500, {.earlyExitRange = 30}, false);
    chassis.moveDistance(10, 500, {}, false);
    chassis.turnToHeading(-174, 500, {}, false);
    // chassis.moveDistance(-10.7, 800, {.forwards = false}, false);
    // chassis.turnToHeading(177, 550, {}, false);
    shotgun.move(-70);
    intake.move(-128);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.moveDistance(-23.5, 1000, {.forwards = false}, false);
    shotgun.move(0);
    intake.move(0);
    chassis.turnToHeading(205, 600, {}, false);
}

void leftBonus() {
    chassis.setPose(LeftStandardStart);
    Intake();
    drop.extend();
    chassis.moveDistance(18, 800, {.minSpeed = 35, .earlyExitRange = 5}, false);
    moveWithVoltage(25, 50);
    pros::delay(450);
    matchloader.extend();
    pros::delay(150);
    // chassis.moveDistance(-5, 500, {.forwards = false}, false);
    // chassis.moveToPose(48, -72, 180, 2500, {.lead = 0.5, .maxSpeed = 80, .minSpeed = 45}, false);
    chassis.turnToPoint(-48, -47, 500, {}, false);
    chassis.moveToPoint(-48, -47, 900, {.maxSpeed = 90, .maxAngularSpeed = 10}, false);
    // pros::lcd::print(2, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);

    // pros::delay(250);
    // pros::lcd::print(3, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);

    double x = distanceResetX(true, 0);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);

    chassis.turnToPoint(-48.5, -72, 500, {}, false);

    moveWithVoltage(60, 60);
    pros::delay(450);
    moveWithVoltage(40, 40);
    pros::delay(360);

    chassis.turnToPoint(-48.5, -24, 500, {.forwards = false}, false);

    shotgun.move(-64);
    pros::lcd::print(1, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    chassis.moveToPoint(-48, -27, 700, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-40, -40);
    shotgun.move_velocity(70);
    pros::delay(600);
    stopIntaking();

    //push
    chassis.turnToHeading(135, 500, {.earlyExitRange = 30}, false);
    chassis.moveDistance(10, 500, {}, false);
    chassis.turnToHeading(-174, 500, {}, false);
    // chassis.moveDistance(-10.7, 800, {.forwards = false}, false);
    // chassis.turnToHeading(177, 550, {}, false);
    shotgun.move(-70);
    intake.move(-128);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.moveDistance(-23.5, 1000, {.forwards = false}, false);
    shotgun.move(0);
    intake.move(0);
    chassis.turnToHeading(205, 600, {}, false);
}

void lowGoalSkills() {
    // DO NOT COMMENT TS or GGGGGGGGGGGGGAAAAAAAAAYYYYYY !
    double x;
    double y;


    chassis.setPose(-7, -44.5, 0);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    screenTaskRunning = false;

    // first 2 stacks
    Intake();
    passTheJuice.extend();
    // chassis.moveDistance(26, 800, {.maxSpeed = 75});
    chassis.moveToPoint(-22, -26, 800, {.maxSpeed = 100}, false);
    chassis.waitUntil(20);
    // matchloader.extend();
    chassis.waitUntilDone();
    pros::delay(200);
    //chassis.turnToHeading(30, 300, {}, false);
    // matchloader.retract();

    // chassis.moveDistance(-10, 800, {.forwards = false}, false);
    chassis.turnToPoint(24, -21, 650, {}, false);
    chassis.moveToPoint(20.3, -21, 1100, {.maxSpeed = 100, .maxAngularSpeed = 10}, false);
    chassis.turnToPoint(-4.5, 5, 600, {}, false);
    drop.toggle();
    chassis.moveDistance(13, 700, {}, false);
    intake.move(-29);
    pros::delay(1350);
    chassis.turnToPoint(48, -48, 500, {.forwards=false}, false);
    chassis.moveToPoint(47, -50, 1200, {.forwards=false, .maxSpeed=90, .maxAngularSpeed=10}, false);
    matchloader.extend();
    shotgun.move(-35);
    Intake();
    pros::delay(300);
    chassis.turnToHeading(180, 500, {}, false);

    // reset
    pros::delay(150);
    x = distanceResetX(false, 0);
    chassis.setPose(72-x, chassis.getPose().y, chassis.getPose().theta);
    pros::delay(150);

    chassis.turnToPoint(48, -72, 400, {}, false);
    chassis.moveDistance(20, 600, {.maxSpeed = 45}, false);
    moveWithVoltage(30, 30);
    pros::delay(1500);
    moveWithVoltage(-30, -30);
    pros::delay(150);
    moveWithVoltage(60, 60);
    pros::delay(400);

    

    chassis.moveToPoint(48, -48, 500, {.forwards=false}, false);
    stopIntaking();
    matchloader.retract();

    // hallway
    chassis.turnToHeading(-135, 600, {}, false);
    chassis.moveDistance(-18.5, 580, {.forwards = false}, false);
    descorer.toggle();

    chassis.turnToPoint(62, 38, 550, {.forwards = false}, false);

    pros::delay(100);
    x = distanceResetX(false, 0);
    chassis.setPose(72-x, chassis.getPose().y, chassis.getPose().theta);
    pros::delay(100);

    chassis.moveToPoint(62, 42, 1750, {.forwards=false, .maxSpeed=92, .maxAngularSpeed=10}, false);
    pros::delay(100);

    // reset
    x = distanceResetX(false, 180);
    chassis.setPose(72-x, chassis.getPose().y, chassis.getPose().theta);
    // pros::delay(120);

    y = distanceResetY(200);
    chassis.setPose(chassis.getPose().x, 72-y, chassis.getPose().theta);
    pros::delay(150);

    chassis.turnToPoint(48, 42, 500, {.forwards = false}, false);

    // x = distanceResetX(false, 90);
    // chassis.setPose(chassis.getPose().x, 72-x, chassis.getPose().theta);
    // pros::delay(100);

    descorer.toggle();
    chassis.moveToPoint(49, 42, 550, {.forwards = false, .maxSpeed = 60, .maxAngularSpeed=10}, false);
    chassis.turnToPoint(48.6, 24, 500, {.forwards=false}, false);
    Intake();
    chassis.moveDistance(-20, 600, {.forwards = false}, false);

    moveWithVoltage(-50, -50);
    passTheJuice.retract();
    pros::delay(100);
    ScoreS(900);
    pros::delay(50);
    stopIntaking();
    resetArm();
    intake.move(-128);


    // reset again
    pros::delay(100);
    resetArm();
    x = distanceResetX(true, 0);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(100);



    //matchload 2
    matchloader.extend();
    chassis.moveToPoint(47, 48, 600, {.maxSpeed = 85, .maxAngularSpeed=10}, false);
    passTheJuice.extend();
    chassis.turnToPoint(47.5, 72, 300, {}, false);
    Intake();
    chassis.moveDistance(20, 600, {.maxSpeed = 45}, false);
    shotgun.move(-35);
    moveWithVoltage(30, 30);
    pros::delay(1500);
    moveWithVoltage(-30, -30);
    pros::delay(150);
    moveWithVoltage(60, 60);
    pros::delay(600);
    

    //long goal score 2
    chassis.moveToPoint(47.8, 27, 700, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    matchloader.retract();
    moveWithVoltage(-50, -50);
    passTheJuice.retract();
    pros::delay(100);
    ScoreS(900);
    pros::delay(100);
    resetArm();
    intake.move(-128);

    // CHECKPOINT HERE

    chassis.setPose(48, 31, chassis.getPose().theta); // change theta
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    drop.extend();
    pros::delay(100);
    chassis.moveToPoint(42, 54, 800, {.maxSpeed=80, .maxAngularSpeed=15}, false);
    passTheJuice.extend();
    chassis.moveToPose(24, 64.2, -110, 90, {.lead = 0.3, .maxSpeed=100}, false);
    chassis.moveToPoint(18, 64.7, 800, {.maxSpeed=100}, false);
    chassis.turnToHeading(-87, 500, {}, false);
    moveWithVoltage(-20, -20);
    pros::delay(150);
    shotgun.move(-128);


    //chassis.setPose(0, 0, 90);
    matchloader.extend();
    pros::delay(200);
    odomLift.retract();
    // chassis.moveDistance(20, 600, {}, false);
    moveWithVoltage(95, 95);
    Intake();
    pros::delay(550);
    
    shotgun.move(-40);
    // double parkBump = distanceResetY(90);
    int counter = 0;
    pros::delay(50);
    moveWithVoltage(75, 70);
    double currDistanceY;
    matchloader.retract();
    while (counter < 2000) {
        currDistanceY = distanceResetY(-90);
        if (currDistanceY < 45 || currDistanceY > 144) {
            counter += 20;
            pros::delay(20);
            continue;
        }
        // printf("y: %f \n", currDistanceY);
        // if (counter < 41) {
        //     matchloader.retract();
        // }

        if (currDistanceY > 72) {
            break;
        }

        pros::delay(20); 
        counter += 20;

        printf("distance sensor: %f\n", currDistanceY);
    }
    
    double parkClear = distanceResetY(-90);
    moveWithVoltage(0, 0);
    pros::delay(200);

    printf("\n\n\n\n\n\nGAP\n\n\n\n\n\n\n");

    counter = 0;
    moveWithVoltage(65, 55);
    while (counter < 2000) {
        currDistanceY = distanceResetY(-90);
        if (currDistanceY < 70 || currDistanceY > 144) {
            counter += 20;
            pros::delay(20);
            continue;
        }
        // printf("y: %f \n", currDistanceY);
        if (currDistanceY > 89 && currDistanceY < 95) {
            matchloader.extend();
        }

        if (currDistanceY > 95) {
            break;
        }

        pros::delay(20); 
        counter += 20;

        printf("distance sensor: %f\n", currDistanceY);
    }
    moveWithVoltage(0, 0);
    pros::delay(200);

    // reset after clear
    odomLift.extend();
    x = distanceResetX(true, -90);
    chassis.setPose(chassis.getPose().x, (72-x), chassis.getPose().theta);
    pros::delay(200);

    // chassis.moveDistance(-6, 500, {}, false);
    chassis.turnToHeading(180, 700, {}, false);

    // resetArm();
    printf("\n\n\n\n\n\n\n\n Y RESET AFTER CLEAR: %f\n\n\n\n\n\n\n\n", chassis.getPose().y);

    
    pros::delay(100);
    x = distanceResetX(true, 180);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);
    printf("\n\n\n\n\n\n\n\n X RESET AFTER CLEAR: %f\n\n\n\n\n\n\n\n", chassis.getPose().x);
    pros::delay(100);


    matchloader.retract();   
    chassis.turnToPoint(-24, 24, 500, {}, false);
    matchloader.retract();
    chassis.moveToPoint(-27, 24, 800, {.maxSpeed=90, .maxAngularSpeed=15}, false);
    drop.extend();
    chassis.turnToPoint(6, -5, 700, {}, false);
    stopIntaking();
    chassis.moveDistance(18, 800, {.maxSpeed=60}, false);
    intake.move(-24);
    pros::delay(1200);
    intake.move(-14);
    pros::delay(200);
    moveWithVoltage(-10, -10);
    pros::delay(300);
    moveWithVoltage(0, 0);
    pros::delay(1100);
    moveWithVoltage(-28, -28);
    intake.move(-12);
    pros::delay(500);
    stopIntaking();
    chassis.moveDistance(-15, 900, {.forwards=false, .maxSpeed=25}, false);
    intake.move(-128);
    chassis.moveToPoint(-45.8, 48, 1100, {.forwards=false, .maxSpeed=95, .maxAngularSpeed=10}, false);
    matchloader.extend();
    shotgun.move(-35);
    Intake();
    pros::delay(300);
    chassis.turnToHeading(0, 550, {}, false);

    // reset
    pros::delay(100);
    x = distanceResetX(false, 0);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(100);

    chassis.turnToPoint(-47.5, 72, 700, {}, false);
    chassis.moveDistance(20, 600, {.maxSpeed = 45}, false);
    moveWithVoltage(30, 30);
    pros::delay(1500);
    moveWithVoltage(-30, -30);
    pros::delay(150);
    moveWithVoltage(60, 60);
    pros::delay(400);

    

    chassis.moveToPoint(-48, 48, 500, {.forwards=false}, false);
    stopIntaking();
    matchloader.retract();

    // hallway
    chassis.turnToHeading(45, 650, {}, false);
    chassis.moveDistance(-18, 800, {.forwards=false}, false);
    
    chassis.turnToPoint(-65, -42, 500, {.forwards=false}, false);
    descorer.toggle();

    //reset
    x = distanceResetX(false, -180);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(100);

    chassis.moveToPoint(-64, -42, 1650, {.forwards=false, .maxSpeed=92, .maxAngularSpeed=10}, false);
    pros::delay(200);

    

    //reset
    x = distanceResetX(false, -180);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(100);

    y = distanceResetY(0);
    chassis.setPose(chassis.getPose().x, -(72-y), chassis.getPose().theta);
    pros::delay(100);

    chassis.turnToPoint(-48, -42, 500, {.forwards = false}, false);

    chassis.moveToPoint(-49.5, -42, 500, {.forwards = false, .maxAngularSpeed=10}, false);
    chassis.turnToPoint(-48.3, -24, 500, {.forwards=false}, false);
    descorer.toggle();
    Intake();
    chassis.moveDistance(-20, 650, {.forwards = false}, false);
    moveWithVoltage(-50, -50);
    passTheJuice.retract();
    pros::delay(100);
    ScoreS(900);
    pros::delay(100);
    stopIntaking();
    resetArm();
    intake.move(-128);


    // reset again
    pros::delay(100);
    resetArm();
    x = distanceResetX(true, 180);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(100);



    //matchload 2
    matchloader.extend();
    chassis.moveToPoint(-47.5, -50, 500, {.maxSpeed = 85, .maxAngularSpeed=10}, false);
    passTheJuice.extend();
    chassis.turnToPoint(-48, -72, 300, {}, false);
    Intake();
    chassis.moveDistance(20, 640, {.maxSpeed = 45}, false);
    stopArm();

    moveWithVoltage(30, 30);
    pros::delay(1500);
    moveWithVoltage(-30, -30);
    pros::delay(150);
    moveWithVoltage(60, 60);
    pros::delay(400);
    

    //long goal score 2
    chassis.moveToPoint(-47.8, -27, 700, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    matchloader.retract();
    moveWithVoltage(-50, -50);
    passTheJuice.retract();
    pros::delay(100);
    ScoreS(900);
    pros::delay(100);
    resetArm();
    intake.move(-128);

    // reset again

    chassis.setPose(-48, -31, chassis.getPose().theta); // change theta
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    drop.extend();
    pros::delay(100);
    chassis.moveToPoint(-42, -54, 800, {.maxSpeed=80, .maxAngularSpeed=15}, false);
    chassis.moveToPose(-24, -64.2, 70, 90, {.lead = 0.3, .maxSpeed=100}, false);
    chassis.moveToPoint(-18, -64.7, 800, {.maxSpeed=100}, false);
    chassis.turnToHeading(93, 500, {}, false);
    moveWithVoltage(-20, -20);
    pros::delay(150);
    shotgun.move(-128);


    //chassis.setPose(0, 0, 90);
    matchloader.extend();
    pros::delay(200);
    odomLift.retract();
    // chassis.moveDistance(20, 600, {}, false);
    moveWithVoltage(95, 95);
    Intake();
    pros::delay(550);
    
    shotgun.move(-40);
    while (distanceResetY(90) < 73.2) {
        moveWithVoltage(70, 70);
        if (distanceResetY(90) > 144) {
            pros::delay(20);
            continue;
        }
        pros::delay(20);
        if (distanceResetY(-90) > 65 && distanceResetY(-90) < 70) {
            matchloader.retract();
        } 
    }
    
    matchloader.retract();
    moveWithVoltage(0, 0);
    pros::delay(670);
    descorer.extend();
}

void noSkills() {
    
    chassis.setPose(LeftStandardStart);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    shotgun.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    screenTaskRunning = false;

    // first 2 stacks
    Intake();
    chassis.moveDistance(26, 800, {.maxSpeed = 75});
    chassis.waitUntil(20);
    matchloader.extend();
    chassis.waitUntilDone();
    pros::delay(200);
    //chassis.turnToHeading(30, 300, {}, false);
    matchloader.retract();
    chassis.turnToPoint(-47.5, 0, 650, {}, false);
    chassis.moveDistance(26, 800, {});
    chassis.waitUntil(20);
    matchloader.extend();
    chassis.waitUntilDone();
    pros::delay(100);
    chassis.moveDistance(-24, 800, {.forwards = false}, false);
    stopIntaking();
    matchloader.retract();
    chassis.turnToPoint(-6, -5, 700, {.forwards = false}, false);
    chassis.moveDistance(-20, 650, {.forwards = false}, false);
    pros::delay(50);

    // score middle goal
    Score(35);
    pros::delay(1000);
    resetArm();

    
    intake.move(-128);
    pros::delay(250);
    drop.toggle();
    resetArm();
    stopIntaking();

    // go to matchload
    matchloader.extend();
    chassis.moveToPoint(-48, -48, 1300, {.maxSpeed = 80, .maxAngularSpeed=10}, false);
    stopArm();

    double x = distanceResetX(true, 0);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);

    chassis.turnToPoint(-47.75, -72, 650, {}, false);
    Intake();

    // matchload 1
    chassis.moveDistance(20, 640, {.maxSpeed = 60}, false);
    moveWithVoltage(40, 40);
    pros::delay(1900);
    moveWithVoltage(-30, -30);
    pros::delay(150);
    moveWithVoltage(60, 60);
    pros::delay(400);

    // hallway
    shotgun.move(-35);
    chassis.moveToPoint(-48, -48, 500, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    chassis.turnToHeading(135, 600, {}, false);
    stopIntaking();
    chassis.moveDistance(-18, 700, {.forwards = false}, false);
    chassis.turnToPoint(-59, 48, 600, {.forwards=false}, false);
    matchloader.retract();
    chassis.moveToPoint(-59, 48, 1800, {.forwards=false, .maxSpeed=85}, false);

    pros::delay(100);


    // reset
    x = distanceResetX(true, 0);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);

    pros::delay(100);

    // long goal score 1
    Intake();
    chassis.turnToPoint(-48,48,500, {}, false);
    chassis.moveDistance(10, 700, {}, false);
    chassis.turnToPoint(-48, 24, 600, {.forwards=false}, false);
    chassis.moveDistance(-20, 700, {.forwards = false}, false);
    //chassis.moveToPose(-48, 24, 0, 1850, {.forwards = false, .lead = .6}, false);
    moveWithVoltage(-50, -50);
    pros::delay(200);
    Score(35);
    pros::delay(800);
    stopIntaking();
    resetArm();
    intake.move(-128);


    // reset again
    pros::delay(150);
    resetArm();
    x = distanceResetX(false, 0);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(150);



    //matchload 2
    matchloader.extend();
    chassis.moveToPoint(-47, 48, 700, {.maxSpeed = 85, .maxAngularSpeed=10}, false);
    chassis.turnToPoint(-46.7, 72, 300, {}, false);
    Intake();
    chassis.moveDistance(20, 640, {.maxSpeed = 67}, false);
    stopArm();

    moveWithVoltage(40, 40);
    pros::delay(1900);
    moveWithVoltage(-30, -30);
    pros::delay(150);
    moveWithVoltage(60, 60);
    pros::delay(400);
    

    //long goal score 2
    chassis.moveToPoint(-48, 27, 700, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    matchloader.retract();
    moveWithVoltage(-50, -50);
    pros::delay(100);
    Score(35);
    pros::delay(800);
    resetArm();
    intake.move(-128);

    // reset again
    pros::delay(150);
    x = distanceResetX(false, 0);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(150);

    // CHECKPOINT HERE
    // chassis.setPose(-48, 31, 0);
    chassis.moveToPoint(-42, 51, 1100, {.maxSpeed=80, .maxAngularSpeed=15}, false);
    chassis.moveToPose(-24, 62, 70, 1250, {.lead = 0.3, .maxSpeed=100}, false);
    chassis.moveToPoint(-16.25, 62, 1000, {.maxSpeed=100}, false);
    chassis.turnToHeading(90, 500, {}, false);
    shotgun.move(-128);


    //chassis.setPose(0, 0, 90);
    matchloader.extend();
    pros::delay(100);
    odomLift.retract();
    // chassis.moveDistance(20, 600, {}, false);
    moveWithVoltage(80, 80);
    Intake();
    pros::delay(350);
    matchloader.retract();
    
    shotgun.move(-40);
    // Intake();
    // //chassis.moveDistance(-13, 800, {.forwards=false}, false);
    // chassis.turnToHeading(90, 700, {}, false);
    // matchloader.retract();
    // //chassis.turnToHeading(90, 700, {}, false);
    
    moveWithVoltage(60, 60);
    pros::delay(630);
    moveWithVoltage(0, 0);
    pros::delay(400);
    moveWithVoltage(55, 55);
    pros::delay(1700);
    moveWithVoltage(0, 0);
    pros::delay(500);

    // reset after clear
    odomLift.extend();
    x = distanceResetX(false, 90);
    chassis.setPose(chassis.getPose().x, (72-x), chassis.getPose().theta);
    chassis.turnToHeading(180, 700, {}, false);
    intake.move(-128);
    pros::delay(1000);
    // resetArm();
    printf("\n\n\n\n\n\n\n\n Y RESET AFTER CLEAR: %f\n\n\n\n\n\n\n\n", chassis.getPose().y);

    x = distanceResetX(false, 0);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);
    printf("\n\n\n\n\n\n\n\n X RESET AFTER CLEAR: %f\n\n\n\n\n\n\n\n", chassis.getPose().x);


    // chassis.moveToPoint(24, 24, 1200, {.forwards=false, .maxSpeed=90, .maxAngularSpeed=20}, false);
    // chassis.turnToPoint(0, 0, 800, {.forwards = false}, false);
    // chassis.moveDistance(-18, 650, {.forwards = false}, false);
    // pros::delay(50);

    // Score(20);
    // pros::delay(2000);
    // resetArm();

    chassis.turnToPoint(48, 48, 600, {}, false);    
    chassis.moveToPoint(48, 48, 3000, {.maxSpeed=90, .maxAngularSpeed=20}, false);
    //drop.toggle();
    chassis.turnToHeading(0, 600, {}, false);
    shotgun.move(0);
    Intake();
    // chassis.moveDistance(10, 600, {}, false);
    // chassis.moveDistance(-10, 600, {.forwards=false}, false);

    // reset
    pros::delay(150);
    x = distanceResetX(true, 0);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);
    matchloader.extend();
    pros::delay(150);
    chassis.turnToPoint(48, 72, 700, {}, false);

    // matchload 3
    chassis.moveDistance(20, 640, {.maxSpeed = 60}, false);
    moveWithVoltage(40, 40);
    pros::delay(1900);
    moveWithVoltage(-30, -30);
    pros::delay(150);
    moveWithVoltage(60, 60);
    pros::delay(400);

    // hallway
    shotgun.move(-50);
    chassis.moveToPoint(48, 48, 800, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    chassis.turnToHeading(-45, 600, {}, false);
    stopIntaking();
    chassis.moveDistance(-18.5, 700, {.forwards = false}, false);
    drop.extend();
    chassis.turnToHeading(0, 600, {}, false);
    matchloader.retract();
    chassis.moveToPoint(60, -48, 1800, {.forwards=false, .maxSpeed=85}, false);

    pros::delay(100);


    // reset
    x = distanceResetX(true, 0);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);

    pros::delay(100);

    // long goal score 3
    Intake();
    //chassis.moveToPose(48, -24, 180, 1850, {.forwards = false, .lead = .55}, false);
    chassis.turnToPoint(48, -48 , 600, {}, false);
    chassis.moveDistance(10, 700, {}, false);
    chassis.turnToPoint(48, -24, 600, {.forwards=false}, false);
    chassis.moveDistance(-15, 700, {.forwards = false}, false);
    moveWithVoltage(-50, -50);
    pros::delay(200);
    Score(35);
    pros::delay(800);
    stopIntaking();
    
    //resetArm();
    intake.move(-128);
    shotgun.move(-70);


    // reset again
    pros::delay(150);
    x = distanceResetX(false, 0);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(150);



    //matchload 2
    matchloader.extend();
    Intake();
    chassis.moveToPoint(47, -48, 700, {.maxSpeed = 85, .maxAngularSpeed=10}, false);

    chassis.turnToPoint(46.2, -72, 500, {}, false);
    chassis.moveDistance(20, 640, {.maxSpeed = 67}, false);
    stopArm();

    moveWithVoltage(40, 40);
    pros::delay(1900);
    moveWithVoltage(-30, -30);
    pros::delay(150);
    moveWithVoltage(60, 60);
    pros::delay(400);

    //long goal score 4
    chassis.moveToPoint(48, -27, 700, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    matchloader.retract();
    moveWithVoltage(-50, -50);
    pros::delay(100);
    Score(35);
    pros::delay(800);
    resetArm();
    intake.move(-128);


    // PARK

    // reset again
    pros::delay(150);
    x = distanceResetX(false, 180);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(150);    

    chassis.moveToPoint(42, -51, 1100, {.maxSpeed=80, .maxAngularSpeed=15}, false);
    chassis.moveToPose(24, -62, -110, 1250, {.lead = 0.3, .maxSpeed=100}, false);
    chassis.moveToPoint(16.25, -62, 1000, {.maxSpeed=100}, false);
    chassis.turnToHeading(-90, 500, {}, false);
    shotgun.move(-128);


    //chassis.setPose(0, 0, 90);
    matchloader.extend();
    pros::delay(100);
    odomLift.retract();
    // chassis.moveDistance(20, 600, {}, false);
    moveWithVoltage(80, 80);
    Intake();
    pros::delay(350);
    matchloader.retract();
    
    shotgun.move(-40);
    // Intake();
    // //chassis.moveDistance(-13, 800, {.forwards=false}, false);
    // chassis.turnToHeading(90, 700, {}, false);
    // matchloader.retract();
    // //chassis.turnToHeading(90, 700, {}, false);
    
    moveWithVoltage(60, 60);
    pros::delay(630);
    moveWithVoltage(0, 0);
    pros::delay(400);
}

void leftAWP() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    screenTaskRunning = false;
    chassis.setPose(leftAWPStart);
    drop.toggle();
    chassis.moveDistance(28, 800, {}, false);
    chassis.turnToPoint(-48, -72, 600, {}, false);
    Intake();
    matchloader.extend();
    pros::delay(250);
    moveWithVoltage(60, 60);
    pros::delay(450);
    moveWithVoltage(40, 40);
    pros::delay(700);

    chassis.moveToPoint(-48, -27, 800, {.forwards = false, .maxSpeed = 80, .maxAngularSpeed = 10}, false);
    pros::lcd::print(1, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    printf("x: %f, y: %f, t: %f\n", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    shotgun.move_velocity(70);
    moveWithVoltage(-50, -50);
    pros::delay(620);
    double x = distanceResetX(true,0);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);
    stopIntaking();
    matchloader.retract();
    armMoving = false;
    stopIntaking();
    pros::delay(300);
    matchloader.retract();

    // both 3 stacks
    // chassis.moveDistance(10, 500, {}, false);
    resetArm();
    intake.move(-128);
    chassis.turnToPoint(24, -22, 750, {}, false);
    Intake();
    pros::delay(50);
    chassis.moveToPoint(-21, -23.5, 800, {.maxSpeed = 80, .maxAngularSpeed = 12, .minSpeed = 35, .earlyExitRange = 10}, false);
    stopArm();
    moveWithVoltage(50, 30);
    pros::delay(200);
    matchloader.extend();
    // drop.toggle();
    pros::delay(300);
    moveWithVoltage(0, 0);
    pros::delay(400);
    // chassis.moveDistance(-17, 800, {.forwards = false}, false);
    matchloader.retract();
    chassis.moveToPoint(-34.5, -28, 800, {.forwards = false}, false);
    chassis.turnToPoint(-47.5, -3, 600, {}, false);
    chassis.moveDistance(16.2, 800, {.maxSpeed=70});
    chassis.waitUntil(13);
    matchloader.extend();
    chassis.waitUntilDone();

    
    
    
    
    // chassis.moveToPose(-45, -7, -15, 2200, {.lead = 0.4, .maxSpeed = 65});
    // chassis.waitUntil(8);
    // matchloader.retract();
    // // chassis.waitUntil(32);
    // // matchloader.extend();
    // chassis.waitUntilDone();
    // matchloader.extend();
    // pros::delay(200);
    // // chassis.moveToPoint(-28, -22, 1000, {.forwards = false, .maxSpeed = 70}, false);
    // chassis.moveDistance(-5, 450, {.forwards = false}, false);
    pros::delay(200);
    chassis.turnToPoint(-24, -24, 500, {.forwards = false}, false);
    drop.toggle();
    matchloader.retract();
    chassis.moveToPoint(-26.5, -23.5, 800, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    chassis.turnToPoint(-4.5, -5, 600, {.forwards = false}, false);
    chassis.moveDistance(-20, 700, {.forwards = false}, false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    shotgun.move_velocity(30);
    pros::delay(1000);
    moveWithVoltage(25, 25);
    pros::delay(300);
    // moveWithVoltage(-20, -20);
    shotgun.move(-70);
    pros::delay(700);
    moveWithVoltage(0, 0);
}


void rightAWP() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    screenTaskRunning = false;
    chassis.setPose(rightAWPStart);
    drop.toggle();
    chassis.moveDistance(27.7, 800, {}, false);
    chassis.turnToHeading(180, 600, {}, false);
    Intake();
    matchloader.extend();
    pros::delay(250);
    moveWithVoltage(40, 40);
    pros::delay(550);
    moveWithVoltage(60, 60);
    pros::delay(700);
    chassis.moveToPoint(47.5, -27, 800, {.forwards = false, .maxSpeed = 80, .maxAngularSpeed = 10}, false);
    pros::lcd::print(1, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    printf("x: %f, y: %f, t: %f\n", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    shotgun.move_velocity(70);
    moveWithVoltage(-50, -50);
    pros::delay(700);
    double x = distanceResetX(false, 180);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);
    stopIntaking();
    matchloader.retract();
    armMoving = false;
    stopIntaking();
    pros::delay(300);
    matchloader.retract();

    // chassis.moveDistance(10, 500, {}, false);
    resetArm();
    intake.move(-128);
    chassis.turnToPoint(24, -24.6, 750, {}, false);
    Intake();
    pros::delay(50);
    chassis.moveToPoint(21, -23.5, 800, {.maxSpeed = 80, .maxAngularSpeed = 12, .minSpeed = 35, .earlyExitRange = 10}, false);
    stopArm();
    moveWithVoltage(30, 50);
    pros::delay(200);
    matchloader.extend();
    // drop.toggle();
    pros::delay(300);
    moveWithVoltage(0, 0);
    pros::delay(400);
    // chassis.moveDistance(-17, 800, {.forwards = false}, false);
    // matchloader.retract();
    // chassis.turnToPoint(48, -1, 600, {}, false);
    // chassis.moveDistance(18, 1000, {.maxSpeed=70}, false);

    
    
    
    
    // chassis.moveToPose(-45, -7, -15, 2200, {.lead = 0.4, .maxSpeed = 65});
    // chassis.waitUntil(8);
    // matchloader.retract();
    // // chassis.waitUntil(32);
    // // matchloader.extend();
    // chassis.waitUntilDone();
    // matchloader.extend();
    // pros::delay(200);
    // // chassis.moveToPoint(-28, -22, 1000, {.forwards = false, .maxSpeed = 70}, false);
    // chassis.moveDistance(-5, 450, {.forwards = false}, false);
    // chassis.turnToPoint(24, -24, 500, {.forwards = false}, false);
    // chassis.moveToPoint(22, -23.5, 800, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    chassis.moveDistance(-7, 500, {.forwards = false}, false);
    matchloader.retract();
    chassis.turnToPoint(4, -5, 600, {}, false);
    chassis.moveDistance(14, 700, {}, false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    intake.move(-38);
    // chassis.turnToPoint(48, -48, 400, {.forwards=false}, false);
    pros::delay(1100);
    intake.move(0);
    chassis.moveToPoint(33.5, -34, 950, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    chassis.turnToHeading(6, 600, {}, false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.moveDistance(24, 750, {.maxSpeed=100}, false);
    chassis.turnToHeading(-30, 500, {.minSpeed=60}, false);
}

void longLowMid() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    screenTaskRunning = false;
    chassis.setPose(rightAWPStart);
    drop.toggle();
    chassis.moveToPoint(46, -48, 900, {}, false);
    chassis.turnToPoint(47.8, -72, 600, {}, false);
    Intake();
    matchloader.extend();
    pros::delay(250);
    moveWithVoltage(40, 40);
    pros::delay(550);
    moveWithVoltage(60, 60);
    pros::delay(700);
    chassis.moveToPoint(47.5, -27, 800, {.forwards = false, .maxSpeed = 80, .maxAngularSpeed = 10}, false);
    pros::lcd::print(1, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    printf("x: %f, y: %f, t: %f\n", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    shotgun.move_velocity(70);
    moveWithVoltage(-50, -50);
    pros::delay(700);
    double x = distanceResetX(false, 180);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);
    stopIntaking();
    matchloader.retract();
    armMoving = false;
    stopIntaking();
    pros::delay(250);
    matchloader.retract();

    // chassis.moveDistance(10, 500, {}, false);
    resetArm();
    intake.move(-128);
    chassis.turnToPoint(24, -25.4, 750, {}, false);
    Intake();
    pros::delay(50);
    chassis.moveToPoint(21, -23.5, 800, {.maxSpeed = 80, .maxAngularSpeed = 12, .minSpeed = 35, .earlyExitRange = 10}, false);
    stopArm();
    moveWithVoltage(30, 50);
    pros::delay(250);
    matchloader.extend();
    // drop.toggle();
    pros::delay(300);
    moveWithVoltage(0, 0);
    pros::delay(250);

    chassis.moveDistance(-7, 500, {.forwards = false}, false);
    matchloader.retract();
    chassis.turnToPoint(4, -5, 600, {}, false);
    chassis.moveDistance(14, 700, {}, false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    intake.move(-50);
    // chassis.turnToPoint(48, -48, 400, {.forwards=false}, false);
    pros::delay(1050);
    intake.move(0);
    chassis.moveToPoint(24.5, -24.5, 600, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    Intake();
    chassis.turnToPoint(-25, -24, 600, {}, false);
    chassis.moveToPoint(-17, -24, 950, {.maxSpeed = 85, .maxAngularSpeed = 5, .minSpeed = 35, .earlyExitRange = 5});
    // chassis.moveToPose(-20, -24, -90, 1800, {.lead = 0.35, .minSpeed = 40, .U30 = false});

    chassis.waitUntilDone();
    moveWithVoltage(25, 40);
    pros::delay(60);
    matchloader.extend();
    pros::delay(370);

    // score on mid goal
    // chassis.moveDistance(-3, 400, {.forwards=false}, false);
    matchloader.retract();
    chassis.turnToPoint(-4, -5, 600, {.forwards = false}, false);
    drop.retract();
    chassis.moveDistance(-18.5, 600, {.forwards = false, .maxSpeed = 70}, false);

    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    shotgun.move_velocity(41);
    pros::delay(1000);
    shotgun.move(-70);
    drop.extend();
    chassis.moveDistance(7, 400, {}, false);
    shotgun.move_velocity(60);
    pros::delay(100);
    passTheJuice.extend();
    chassis.moveDistance(-12, 400, {.forwards = false});
    // moveWithVoltage(-20, -20);
    shotgun.move(-70);
    pros::delay(700);
    moveWithVoltage(0, 0);
}

void soloSigAWP() {
    shotgunRS.reset_position();
    chassis.setPose(rightAWPStart);
    screenTaskRunning = false;
    drop.toggle();
    Intake();
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

    //preload
    // chassis.moveDistance(14, 450, {}, false);
    // pros::delay(100);

    //matchload
    chassis.moveToPoint(47, -48, 900, { .maxSpeed = 85, .maxAngularSpeed = 10}, false);
    chassis.turnToPoint(47, -72, 600, {}, false);
    matchloader.extend();
    Intake();
    shotgun.move(0);
    chassis.waitUntilDone();
    chassis.moveDistance(20, 600, {.maxSpeed = 50}, false);
    moveWithVoltage(35, 35);
    pros::delay(675);

    // !right long goal
    chassis.moveToPoint(47.7, -27, 900, {.forwards = false, .maxSpeed = 80, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-50, -50);
    Score(45);
    pros::delay(450);


    armMoving = false;
    stopIntaking();
    pros::delay(100);
    matchloader.retract();

    // !both 3 stacks
    // chassis.moveDistance(10, 500, {}, false);
    resetArm();
    intake.move(-128);
    chassis.turnToPoint(24, -24.4, 750, {}, false);
    Intake();
    pros::delay(50);
    chassis.moveToPoint(21, -23.2, 800, {.maxSpeed = 80, .maxAngularSpeed = 12, .minSpeed = 35, .earlyExitRange = 10}, false);
    stopArm();
    moveWithVoltage(30, 50);
    matchloader.extend();
    pros::delay(200);
    pros::delay(25);
    chassis.turnToPoint(-24.6, -23.6, 550, {}, false);
    matchloader.retract();
    shotgun.move(-55);
    chassis.moveToPoint(-17, -24, 1050, {.maxSpeed = 75, .maxAngularSpeed = 5, .minSpeed = 40, .earlyExitRange = 6});
    // chassis.moveToPose(-20, -24, -90, 1800, {.lead = 0.35, .minSpeed = 40, .U30 = false});
    chassis.waitUntilDone();
    moveWithVoltage(32, 32);
    matchloader.extend();
    moveWithVoltage(27, 27);
    pros::delay(250);


    
    chassis.moveToPoint(-48, -50, 900, {.maxSpeed = 90}, false);


    chassis.turnToPoint(-47.8, -24, 450, {.forwards = false}, false);
    Intake();
    chassis.moveDistance(-20, 400, {.forwards = false}, false);
    moveWithVoltage(-40, -40);
    pros::delay(100);
    Score(45);
    // reset 
    pros::delay(450);
    double x = distanceResetX(true, 180);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(100);
    resetArm();
    intake.move(-128);

    
    chassis.moveToPoint(-47.5, -48, 600, {.maxSpeed = 80, .maxAngularSpeed = 10, .minSpeed = 60});
    chassis.turnToPoint(-47.5, -72, 150, {}, false);
    chassis.moveDistance(20, 600, {.maxSpeed = 50}, false);
    Intake();
    shotgun.move(0);
    chassis.waitUntilDone();

    moveWithVoltage(35, 35);
    pros::delay(700);

    passTheJuice.extend();
    chassis.moveToPoint(-48, -50, 400, {.forwards = false}, false);
    chassis.turnToPoint(5, 5, 420, {.forwards = false}, false);
    drop.toggle();
    chassis.moveToPoint(-10, -10, 1200, {.forwards = false, .maxSpeed = 90, .maxAngularSpeed = 20}, false);
    Score(30);

    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    pros::delay(800);
    shotgun.move(-70);
    
    shotgun.move_velocity(60);
    chassis.moveDistance(6, 600, {}, false);
    drop.extend();
    chassis.moveDistance(-6, 600, {.forwards = false});

    // moveWithVoltage(-20, -20);
    shotgun.move(-70);
    pros::delay(700);
    moveWithVoltage(0, 0);
}

void lowGoalSoloSigAWP() {
    shotgunRS.reset_position();
    chassis.setPose(leftAWPStart);
    screenTaskRunning = false;
    drop.toggle();
    Intake();
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

    //preload
    // chassis.moveDistance(14, 450, {}, false);
    // pros::delay(100);

    //matchload
    chassis.moveToPoint(-46.7, -48, 900, { .maxSpeed = 85, .maxAngularSpeed = 10}, false);
    chassis.turnToPoint(-47.5, -72, 525, {}, false);
    matchloader.extend();
    Intake();
    shotgun.move(0);
    chassis.waitUntilDone();
    chassis.moveDistance(20, 600, {.maxSpeed = 65}, false);
    moveWithVoltage(35, 35);
    pros::delay(675);

    // !left long goal
    chassis.moveToPoint(-48.2, -27, 900, {.forwards = false, .maxSpeed = 80, .maxAngularSpeed = 10}, false);
    moveWithVoltage(-50, -50);
    Score(45);
    pros::delay(450);


    armMoving = false;
    stopIntaking();
    pros::delay(100);
    matchloader.retract();

    // !both 3 stacks
    // chassis.moveDistance(10, 500, {}, false);
    resetArm();
    intake.move(-128);
    chassis.turnToPoint(-24, -24.4, 750, {}, false);
    Intake();
    pros::delay(50);
    chassis.moveToPoint(-21, -23.2, 800, {.maxSpeed = 80, .maxAngularSpeed = 12, .minSpeed = 35, .earlyExitRange = 10}, false);
    stopArm();
    moveWithVoltage(50, 30);
    matchloader.extend();
    pros::delay(200);
    pros::delay(25);
    chassis.turnToPoint(24.6, -23.6, 550, {}, false);
    matchloader.retract();
    shotgun.move(-55);
    chassis.moveToPoint(17, -24, 1050, {.maxSpeed = 75, .maxAngularSpeed = 5, .minSpeed = 40, .earlyExitRange = 6});
    // chassis.moveToPose(-20, -24, -90, 1800, {.lead = 0.35, .minSpeed = 40, .U30 = false});
    chassis.waitUntilDone();
    moveWithVoltage(32, 32);
    matchloader.extend();
    moveWithVoltage(27, 27);
    pros::delay(250);


    
    chassis.moveToPoint(46, -50, 800, {.maxSpeed = 90}, false);


    pros::delay(200);
    chassis.turnToPoint(47.3, -24, 450, {.forwards = false}, false);
    Intake();
    chassis.moveDistance(-20, 400, {.forwards = false}, false);
    moveWithVoltage(-40, -40);
    pros::delay(100);
    Score(45);
    // reset 
    pros::delay(450);
    double x = distanceResetX(false, 180);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(100);
    resetArm();
    intake.move(-128);

    chassis.moveToPoint(47.5, -48, 500, {.maxSpeed = 80, .maxAngularSpeed = 10}, false);
    chassis.turnToPoint(47.5, -72, 150, {}, false);
    chassis.moveDistance(20, 600, {.maxSpeed = 50}, false);
    Intake();
    shotgun.move(0);
    chassis.waitUntilDone();

    moveWithVoltage(35, 35);
    pros::delay(700);


    chassis.moveToPoint(48, -50, 500, {.forwards=false}, false);
    matchloader.retract();
    chassis.turnToPoint(-5, 5, 660, {}, false);
    chassis.moveToPoint(5, -5, 1200, {.maxSpeed = 80, .maxAngularSpeed = 20}, false);
    intake.move(-40);

    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    pros::delay(800);
}

void Push4Left() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    screenTaskRunning = false;
    chassis.setPose(leftAWPStart);
    drop.toggle();
    chassis.moveDistance(28, 700, {}, false);
    chassis.turnToPoint(-48, -72, 550, {}, false);
    Intake();
    matchloader.extend();
    pros::delay(100);
    moveWithVoltage(60, 60);
    pros::delay(450);
    moveWithVoltage(40, 40);
    pros::delay(730);

    chassis.moveToPoint(-48, -27, 700, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    pros::lcd::print(1, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    printf("x: %f, y: %f, t: %f\n", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    shotgun.move_velocity(70);
    moveWithVoltage(-50, -50);
    pros::delay(660);
    stopIntaking();
    // matchloader.retract();
    chassis.turnToHeading(135, 400, {.earlyExitRange = 30}, false);
    chassis.moveDistance(10, 500, {}, false);
    chassis.turnToHeading(-174, 500, {}, false);
    // chassis.moveDistance(-10.7, 800, {.forwards = false}, false);
    // chassis.turnToHeading(177, 550, {}, false);
    shotgun.move(-70);
    intake.move(-128);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.moveDistance(-23, 1000, {.forwards = false}, false);
    shotgun.move(0);
    intake.move(0);
    chassis.turnToHeading(205, 800, {}, false);
}

void Push4Right() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    screenTaskRunning = false;
    chassis.setPose(rightAWPStart);
    drop.toggle();
    chassis.moveDistance(28, 700, {}, false);
    chassis.turnToPoint(48, -72, 550, {}, false);
    Intake();
    matchloader.extend();
    pros::delay(100);
    moveWithVoltage(60, 60);
    pros::delay(450);
    moveWithVoltage(40, 40);
    pros::delay(730);

    chassis.moveToPoint(48, -27, 700, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    pros::lcd::print(1, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    printf("x: %f, y: %f, t: %f\n", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    shotgun.move_velocity(70);
    moveWithVoltage(-50, -50);
    pros::delay(660);
    stopIntaking();
    // matchloader.retract();
    chassis.turnToHeading(135, 400, {.earlyExitRange = 30}, false);
    chassis.moveDistance(10, 500, {}, false);
    chassis.turnToHeading(-174, 500, {}, false);
    // chassis.moveDistance(-10.7, 800, {.forwards = false}, false);
    // chassis.turnToHeading(177, 550, {}, false);
    shotgun.move(-70);
    intake.move(-128);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.moveDistance(-23, 1000, {.forwards = false}, false);
    shotgun.move(0);
    intake.move(0);
    chassis.turnToHeading(205, 800, {}, false);
}

void test() {
    chassis.setPose(LeftStandardStart);
    // //pros::delay(5000);
    // printf("=== BEGIN DISTANCE SENSOR TEST ===\n");

    // // Test 1: Ping Y sensor
    // printf("Test 1: Reading Y...\n");
    // int yVal = distanceY.get();
    // printf("Y VALUE = %d\n", yVal);

    // //pros::delay(10);

    // // Test 2: Ping X sensor
    // printf("Test 2: Reading X...\n");
    // int xVal = distanceX.get();
    // printf("X VALUE = %d\n", xVal);

    // //pros::delay(10);

    // printf("=== END TEST ===\n");


    // printf("=== IMU TEST ===\n");
    // printf("Calling imu.get_heading()...\n");
    // pros::delay(200); 
    // double h = imu.get_heading();
    // printf("IMU HEADING = %f\n", h);
    // printf("=== END IMU TEST ===\n");


    // /*printf("\nodom pos\n");
    // printf("X: %f\n", chassis.getPose().x);
    // printf("Y: %f\n", chassis.getPose().y);
    // printf("Theta: %f\n", chassis.getPose().theta);*/


    // double angleDistanceX = (xVal / 25.4) + 4.4;

    // double finalDistanceX = angleDistanceX * cos(lemlib::degToRad(imu.get_heading()));
    // printf("finaldistx: %lf\n", finalDistanceX);
    // double x = fabs(finalDistanceX);


    // double angleDistanceY = (yVal / 25.4) + 4.8;
    // double finalDistanceY = angleDistanceY * cos(lemlib::degToRad(imu.get_heading() ));
    // printf("finaldisty: %lf\n", finalDistanceY);
    // double y = fabs(finalDistanceY);
    // pros::delay(500);

    // chassis.setPose(72 - x, -(72 - y), imu.get_heading());

    // printf("\n sensor pos\n");
    // printf("X: %f\n", chassis.getPose().x);
    // printf("Y: %f\n", chassis.getPose().y);
    // printf("Theta: %f\n", chassis.getPose().theta);

    // chassis.moveToPoint(0, 24, 5000, {}, false);
    // pros::delay(200);
    // chassis.turnToHeading(90, 500, {}, false);

    chassis.moveToPoint(-24, -24, 2000);


    // screenTaskRunning = false;
    // pros::lcd::clear();
    // pros::lcd::set_text(0, "Distance X Left Test");
    // // pros::delay(4000);
    // while(true) {
    //     pros::delay(10);
    //     pros::lcd::print(0, "X: %.4f", distanceResetX(false, 0)); // x
    // }
}

void pidTest() {
    chassis.setPose(-7, -44.5, 0);
    // drop.extend();
    // Intake();
    // pros::delay(7500);
    // descorer.extend();
    // pros::delay(600);
    // stopIntaking();
    // descorer.retract();
    // pros::delay(1000);
    // descorer.extend();
    // // SCORE
    // double error = lemlib::angleError(108, shotgunRS.get_position()/100.0, false);
    // std::vector<float> speeds;
    // ScoreS(800);
    // for (float s : speeds) {
    //     printf("%f\n ", s);
    // }
    // printf("\n");
    // pros::delay(1000);
    // resetArm();
    // intake.move(-128);
    // pros::delay(1000);
    // descorer.retract();
    // Intake();
    // pros::delay(7500);
    // descorer.extend();
    // pros::delay(600);
    // stopIntaking();
    // descorer.retract();
    // pros::delay(1000);
    // descorer.extend();
    // // SCORE
    // error = lemlib::angleError(108, shotgunRS.get_position()/100.0, false);
    // std::vector<float> speeds2;
    // ScoreS(800);
    // for(float s : speeds2) {
    //     printf("%f\n ", s);
    // }
    // pros::delay(1000);
    // resetArm();
    // intake.move(-128);
    // pros::delay(1000);
    // descorer.retract();
    
    
    /*screenTaskRunning = false;
    while(true) {
        pros::delay(50);
        pros::lcd::print(0, "Y: %.4f", 72 - distanceResetY(-90));
        pros::lcd::print(1, "X: %.4f", 72 - distanceResetX(true, 0));
    }*/


    // chassis.setPose(0, 0, 0);
    // chassis.moveDistance(5, 700, {}, false);
    // pros::delay(2000);
    // chassis.setPose(0, 0, 0);
    // chassis.moveDistance(12, 700, {}, false);
    // pros::delay(2000);
    // chassis.setPose(0, 0, 0);
    // chassis.moveDistance(24, 800, {}, false);
    // pros::delay(2000);
    // chassis.setPose(0, 0, 0);
    // chassis.moveDistance(36, 900, {}, false);
    // pros::delay(2000);

    // chassis.setPose(0, 0, 0);
    // // matchloader.extend();
    // pros::delay(1000);
    // chassis.turnToHeading(45, 500, {}, false);
    // printf("heading: %f\n", chassis.getPose().theta);
    // pros::delay(1000);
    // chassis.setPose(0, 0, 0);
    // chassis.turnToHeading(90, 500, {}, false);
    // printf("heading: %f\n", chassis.getPose().theta);
    // pros::delay(1000);
    // chassis.setPose(0, 0, 0);
    // chassis.turnToHeading(135, 600, {}, false);
    // printf("heading: %f\n", chassis.getPose().theta);
    // pros::delay(1000);
    // chassis.setPose(0, 0, 0);
    // chassis.turnToHeading(178, 600, {}, false);
    // printf("heading: %f\n", chassis.getPose().theta);
    // pros::delay(1000);
}


// vector of tuple of function description and pointers
std::vector<std::tuple<std::string, void(*)()>> autons = {
    {"pid test", pidTest},
    {"right bonus", rightBonus},
    {"left bonus", leftBonus},
    {"right AWP", rightAWP},
    {"left AWP", leftAWP},
    {"long low mid", longLowMid},
    {"solo sig AWP", soloSigAWP},
    {"low goal solo sig AWP", lowGoalSoloSigAWP},
    {"4 push right", Push4Right},
    {"4 push left", Push4Left},
    {"skills", noSkills},
    {"low goal skills", lowGoalSkills}


};

