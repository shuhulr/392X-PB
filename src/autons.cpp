#include "autons.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "globals.hpp"
#include <vector>
#include <tuple>
#include "liblvgl/llemu.hpp"
#include "pros/llemu.hpp" // IWYU pragma: keep
#include "pros/motors.h" // IWYU pragma: keep
#include "pros/rtos.hpp" // IWYU pragma: keep
#include <cstddef> // IWYU pragma: keep


// auton num
int autonIndex = 5;

extern bool screenTaskRunning;


lemlib::Pose origin(0, 0, 0);

lemlib::Pose RightStandardStart(17.3, -48.6, 14);
lemlib::Pose LeftStandardStart(-17.3, -48.6, -14);
lemlib::Pose leftAWPStart(-15.75, -49, -90);
lemlib::Pose rightAWPStart(15, -48.5, -90);
lemlib::Pose SoloStart(-10, -45, 20);
lemlib::Pose SoloSigStart(7.4, -47.5, -90);

void rightBonus() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    screenTaskRunning = false;
    chassis.setPose(RightStandardStart);
    Intake();
    drop.extend();
    chassis.moveDistance(18, 800, {.minSpeed = 35, .earlyExitRange = 7}, false);
    moveWithVoltage(50, 25);
    pros::delay(650);
    matchloader.extend();
    pros::delay(200);
    // chassis.moveDistance(-5, 500, {.forwards = false}, false);
    // chassis.moveToPose(48, -72, 180, 2500, {.lead = 0.5, .maxSpeed = 80, .minSpeed = 45}, false);
    chassis.turnToPoint(48, -47, 600, {}, false);
    chassis.moveToPoint(48, -47, 900, {.maxSpeed = 90, .maxAngularSpeed = 10}, false);
    // pros::lcd::print(2, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);

    // pros::delay(250);
    // pros::lcd::print(3, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);

    chassis.turnToPoint(48, -72, 500, {}, false);
    moveWithVoltage(60, 60);
    pros::delay(450);
    moveWithVoltage(40, 40);
    pros::delay(100);
    chassis.turnToPoint(48, -24, 500, {.forwards = false}, false);
    shotgun.move(-64);
    pros::lcd::print(1, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    chassis.moveToPoint(48, -27, 800, {.forwards = false, .maxSpeed = 80, .maxAngularSpeed = 15}, false);
    moveWithVoltage(-40, -40);
    shotgun.move_velocity(60);
    pros::delay(600);
    stopIntaking();
    chassis.moveDistance(9, 700, {}, false);
    chassis.turnToHeading(-115, 600, {}, false);
    chassis.moveDistance(-10.7, 800, {.forwards = false}, false);
    chassis.turnToHeading(177, 600, {}, false);
    shotgun.move(-70);
    intake.move(-128);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.moveDistance(-23, 1000, {.forwards = false}, false);
    shotgun.move(0);
    intake.move(0);
    chassis.turnToHeading(190, 600, {}, false);
}

void leftBonus() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    screenTaskRunning = false;
    chassis.setPose(LeftStandardStart);
    Intake();
    drop.extend();
    chassis.moveDistance(18, 800, {.minSpeed = 35, .earlyExitRange = 7}, false);
    moveWithVoltage(25, 50);
    pros::delay(550);
    matchloader.extend();
    pros::delay(300);
    // chassis.moveDistance(-5, 500, {.forwards = false}, false);
    // chassis.moveToPose(48, -72, 180, 2500, {.lead = 0.5, .maxSpeed = 80, .minSpeed = 45}, false);
    chassis.turnToPoint(-48, -47, 600, {}, false);
    chassis.moveToPoint(-48, -47, 900, {.maxSpeed = 90, .maxAngularSpeed = 10}, false);
    // pros::lcd::print(2, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);

    // pros::delay(250);
    // pros::lcd::print(3, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);

    chassis.turnToPoint(-48, -72, 500, {}, false);
    moveWithVoltage(60, 60);
    pros::delay(450);
    moveWithVoltage(40, 40);
    pros::delay(700);
    chassis.turnToPoint(-48, -24, 500, {.forwards = false}, false);
    shotgun.move(-64);
    pros::lcd::print(1, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    chassis.moveToPoint(-48, -27, 800, {.forwards = false, .maxSpeed = 80, .maxAngularSpeed = 15}, false);
    moveWithVoltage(-40, -40);
    shotgun.move_velocity(80);
    pros::delay(300);
    stopIntaking();
    pros::delay(300);
    chassis.moveDistance(9, 700, {}, false);
    chassis.turnToHeading(-115, 600, {}, false);
    chassis.moveDistance(-10.7, 800, {.forwards = false}, false);
    chassis.turnToHeading(177, 600, {}, false);
    shotgun.move(-70);
    intake.move(-128);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    chassis.moveDistance(-23, 1000, {.forwards = false}, false);
    shotgun.move(0);
    intake.move(0);
    chassis.turnToHeading(190, 600, {}, false);
}

void skills() {
    chassis.setPose(LeftStandardStart);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    screenTaskRunning = false;
    

    // first 2 stacks
    Intake();
    chassis.moveDistance(26, 800, {.maxSpeed = 75}, false);
    pros::delay(200);
    chassis.turnToHeading(30, 300, {}, false);
    chassis.turnToPoint(-47.5, 0, 650, {}, false);
    chassis.moveDistance(25.4, 800, {}, false);
    pros::delay(100);
    chassis.moveDistance(-24, 800, {.forwards = false}, false);
    stopIntaking();
    chassis.turnToPoint(-6, -5, 700, {.forwards = false}, false);
    chassis.moveDistance(-20, 650, {.forwards = false}, false);
    pros::delay(50);

    // score middle goal
    Score(25);
    pros::delay(1000);
    resetArm();

    
    intake.move(-128);
    pros::delay(250);
    drop.toggle();
    resetArm();
    stopIntaking();

    // go to matchload
    matchloader.extend();
    chassis.moveToPoint(-47.5, -48, 1200, {.maxSpeed = 80, .maxAngularSpeed=10}, false);
    stopArm();
    chassis.turnToPoint(-47.5, -72, 650, {}, false);
    Intake();

    // matchload 1
    chassis.moveDistance(20, 640, {.maxSpeed = 60}, false);
    moveWithVoltage(40, 40);
    pros::delay(1800);
    moveWithVoltage(-30, -30);
    pros::delay(150);
    moveWithVoltage(60, 60);
    pros::delay(400);

    // hallway
    shotgun.move(-35);
    chassis.moveToPoint(-48, -48, 500, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    chassis.turnToHeading(135, 600, {}, false);
    stopIntaking();
    chassis.moveDistance(-16.5, 700, {.forwards = false}, false);
    chassis.turnToHeading(180, 600, {}, false);
    matchloader.retract();
    chassis.moveToPoint(-57, 48, 2000, {.forwards=false, .maxSpeed=85}, false);

    pros::delay(100);


    // reset
    double x = distanceResetX(true, 0);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);

    pros::delay(100);

    // long goal score 1
    Intake();
    chassis.moveToPose(-48, 24, 0, 1850, {.forwards = false, .lead = .6}, false);
    moveWithVoltage(-50, -50);
    pros::delay(200);
    Score(35);
    pros::delay(950);
    stopIntaking();
    resetArm();


    // reset again
    pros::delay(150);
    resetArm();
    x = distanceResetX(false, 0);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(150);



    //matchload 2
    matchloader.extend();
    Intake();
    chassis.moveToPoint(-47, 48, 700, {.maxSpeed = 85, .maxAngularSpeed=10}, false);

    chassis.turnToPoint(-47.5, 72, 300, {}, false);
    chassis.moveDistance(20, 640, {.maxSpeed = 67}, false);
    stopArm();

    moveWithVoltage(40, 40);
    pros::delay(1800);
    moveWithVoltage(-30, -30);
    pros::delay(150);
    moveWithVoltage(60, 60);
    pros::delay(400);
    
    /*moveWithVoltage(40, 40);
    pros::delay(700);
    moveWithVoltage(-30, -30);
    pros::delay(100);
    moveWithVoltage(40, 40);
    pros::delay(300);
    moveWithVoltage(-30, -30);
    pros::delay(100);
    moveWithVoltage(50, 50);
    pros::delay(300);
    moveWithVoltage(-30, -30);
    pros::delay(150);
    moveWithVoltage(50, 50);
    pros::delay(200);*/



    //long goal score 2
    chassis.moveToPoint(-48, 27, 700, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    matchloader.retract();
    moveWithVoltage(-50, -50);
    pros::delay(100);
    Score(35);
    pros::delay(950);
    resetArm();

    // reset again
    pros::delay(150);
    x = distanceResetX(false, 0);
    chassis.setPose(-(72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(150);
    
    drop.toggle();
    chassis.moveToPoint(-24, 52, 1300, {}, false);
    chassis.turnToHeading(67, 600, {}, false);

    // reset again
    pros::delay(150);
    x = distanceResetX(false, 90);
    chassis.setPose(chassis.getPose().x, 72-x, chassis.getPose().theta);
    pros::delay(150);

    matchloader.extend();
    chassis.moveDistance(20, 500, {});
    
    chassis.moveDistance(-9, 700, {.forwards=false}, false);
    matchloader.retract();
    chassis.turnToHeading(75, 550, {}, false);
    odomLift.retract();
    
    moveWithVoltage(60, 60);
    pros::delay(1300);
    moveWithVoltage(0, 0);
    pros::delay(300);
    moveWithVoltage(40, 40);
    pros::delay(1000);
    moveWithVoltage(0, 0);
    pros::delay(1000);

    // reset after clear
    odomLift.extend();
    x = distanceResetX(false, 90);
    chassis.setPose(chassis.getPose().x, (72-x), chassis.getPose().theta);
    chassis.turnToHeading(0, 600, {}, false);
    pros::delay(200);
    printf("\n\n\n\n\n\n\n\n Y RESET AFTER CLEAR: %f\n\n\n\n\n\n\n\n", chassis.getPose().y);

    x = distanceResetX(true, 0);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);
    printf("\n\n\n\n\n\n\n\n X RESET AFTER CLEAR: %f\n\n\n\n\n\n\n\n", chassis.getPose().x);


    chassis.moveToPoint(24, 24, 1200, {.forwards=false, .maxSpeed=90, .maxAngularSpeed=20}, false);
    chassis.turnToPoint(0, 0, 800, {.forwards = false}, false);
    chassis.moveDistance(-18, 650, {.forwards = false}, false);
    pros::delay(50);

    Score(20);
    pros::delay(2000);
    resetArm();

    chassis.turnToPoint(48, 48, 600, {}, false);
    chassis.moveToPoint(48, 48, 2000, {.maxSpeed=90, .maxAngularSpeed=20}, false);
    drop.toggle();
    // chassis.moveDistance(10, 600, {}, false);
    // chassis.moveDistance(-10, 600, {.forwards=false}, false);

    // reset
    pros::delay(150);
    x = distanceResetX(true, 0);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);
    matchloader.extend();
    pros::delay(150);
    chassis.turnToPoint(48, 72, 700, {}, false);

    // reset
    pros::delay(150);
    x = distanceResetX(true, 0);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);
    matchloader.extend();
    pros::delay(150);

    // matchload 3
    chassis.moveDistance(20, 640, {.maxSpeed = 60}, false);
    moveWithVoltage(40, 40);
    pros::delay(1800);
    moveWithVoltage(-30, -30);
    pros::delay(150);
    moveWithVoltage(60, 60);
    pros::delay(400);

    // hallway
    shotgun.move(-50);
    chassis.moveToPoint(48, 48, 500, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    chassis.turnToHeading(-45, 600, {}, false);
    stopIntaking();
    chassis.moveDistance(-18.5, 700, {.forwards = false}, false);
    chassis.turnToHeading(0, 600, {}, false);
    matchloader.retract();
    chassis.moveToPoint(60, -48, 2000, {.forwards=false, .maxSpeed=85}, false);

    pros::delay(100);


    // reset
    x = distanceResetX(true, 0);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);

    pros::delay(100);

    // long goal score 3
    Intake();
    chassis.moveToPose(48, -24, 180, 1850, {.forwards = false, .lead = .6}, false);
    moveWithVoltage(-50, -50);
    pros::delay(200);
    Score(35);
    pros::delay(950);
    stopIntaking();
    resetArm();


    // reset again
    pros::delay(150);
    x = distanceResetX(false, 0);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(150);



    //matchload 2
    matchloader.extend();
    Intake();
    chassis.moveToPoint(47, -48, 700, {.maxSpeed = 85, .maxAngularSpeed=10}, false);

    chassis.turnToPoint(47.5, -72, 300, {}, false);
    chassis.moveDistance(20, 640, {.maxSpeed = 67}, false);
    stopArm();

    moveWithVoltage(40, 40);
    pros::delay(1800);
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
    pros::delay(950);
    resetArm();

    // reset again
    pros::delay(150);
    x = distanceResetX(false, 0);
    chassis.setPose((72-x), chassis.getPose().y, chassis.getPose().theta);
    pros::delay(150);    

    chassis.moveToPoint(24, -52, 1300, {}, false);
    chassis.turnToHeading(-113, 600, {}, false);

    matchloader.extend();
    chassis.moveDistance(20, 500, {});
    
    chassis.moveDistance(-9, 700, {.forwards=false}, false);
    matchloader.retract();
    chassis.turnToHeading(75, 550, {}, false);
    odomLift.retract();
    
    moveWithVoltage(60, 60);
    pros::delay(1300);
    moveWithVoltage(0, 0);
    pros::delay(300);


    /*Intake();
    chassis.moveDistance(22, 1200, {.minSpeed = 35, .earlyExitRange = 7}, false);
    moveWithVoltage(20, 20);
    pros::delay(400);

    chassis.turnToPoint(-3, -3, 500, {.forwards = false}, false);
*/
}

void leftAWP() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    screenTaskRunning = false;
    chassis.setPose(leftAWPStart);
    drop.toggle();
    chassis.moveDistance(30, 800, {}, false);
    chassis.turnToPoint(-48, -72, 600, {}, false);
    Intake();
    matchloader.extend();
    pros::delay(250);
    moveWithVoltage(60, 60);
    pros::delay(450);
    moveWithVoltage(40, 40);
    pros::delay(650);

    chassis.moveToPoint(-48, -27, 800, {.forwards = false, .maxSpeed = 80, .maxAngularSpeed = 10}, false);
    pros::lcd::print(1, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    printf("x: %f, y: %f, t: %f\n", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    shotgun.move_velocity(55);
    moveWithVoltage(-50, -50);
    pros::delay(570);
    stopIntaking();
    matchloader.retract();
    chassis.moveDistance(10, 500, {}, false);
    resetArm();
    chassis.turnToPoint(-24, -24, 580, {}, false);
    Intake();
    chassis.moveDistance(18, 800, {.minSpeed = 35, .earlyExitRange = 5.5}, false);
    stopArm();
    moveWithVoltage(35, 35);
    pros::delay(300);
    moveWithVoltage(60, 30);
    pros::delay(300);
    matchloader.extend();
    drop.toggle();
    pros::delay(200);
    moveWithVoltage(0, 0);
    pros::delay(400);
    chassis.moveDistance(-10, 500, {.forwards = false}, false);
    chassis.moveToPose(-45, -7, -15, 2200, {.lead = 0.4, .maxSpeed = 65});
    chassis.waitUntil(8);
    matchloader.retract();
    // chassis.waitUntil(32);
    // matchloader.extend();
    chassis.waitUntilDone();
    matchloader.extend();
    pros::delay(200);
    // chassis.moveToPoint(-28, -22, 1000, {.forwards = false, .maxSpeed = 70}, false);
    chassis.moveDistance(-5, 450, {.forwards = false}, false);
    chassis.turnToPoint(-24, -24, 500, {.forwards = false}, false);
    chassis.moveToPoint(-26.5, -23.5, 800, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    chassis.turnToPoint(-6, -5, 600, {.forwards = false}, false);
    chassis.moveDistance(-20, 700, {.forwards = false}, false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    shotgun.move_velocity(25);
    pros::delay(1000);
    moveWithVoltage(25, 25);
    pros::delay(300);
    moveWithVoltage(-20, -20);
    shotgun.move(-70);
    pros::delay(700);
    moveWithVoltage(0, 0);
}


void rightAWP() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    screenTaskRunning = false;
    chassis.setPose(rightAWPStart);
    drop.toggle();
    chassis.moveDistance(30.5, 800, {}, false);
    chassis.turnToHeading(180, 600, {}, false);
    Intake();
    matchloader.extend();
    pros::delay(250);
    moveWithVoltage(70, 70);
    pros::delay(450);
    moveWithVoltage(40, 40);
    pros::delay(590);
    chassis.moveToPoint(-48, -27, 800, {.forwards = false, .maxSpeed = 80, .maxAngularSpeed = 10}, false);
    pros::lcd::print(1, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    printf("x: %f, y: %f, t: %f\n", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    shotgun.move_velocity(55);
    moveWithVoltage(-50, -50);
    pros::delay(570);
    stopIntaking();
    matchloader.retract();
    chassis.moveDistance(9, 700, {}, false);
    shotgun.move(-70);
    chassis.turnToPoint(-24, -24, 700, {}, false);
    Intake();
    chassis.moveDistance(18, 800, {.minSpeed = 35, .earlyExitRange = 7}, false);
    shotgun.move(0);
    moveWithVoltage(30, 30);
    pros::delay(600);
    matchloader.extend();
    drop.toggle();
    pros::delay(200);
    chassis.moveToPose(-45, -5, -15, 2100, {.lead = 0.35, .maxSpeed = 75});
    chassis.waitUntil(8);
    matchloader.retract();
    // chassis.waitUntil(32);
    // matchloader.extend();
    chassis.waitUntilDone();
    pros::delay(200);
    // chassis.moveToPoint(-28, -22, 1000, {.forwards = false, .maxSpeed = 70}, false);
    chassis.moveDistance(-6, 500, {.forwards = false}, false);
    chassis.turnToPoint(-24, -24, 500, {.forwards = false}, false);
    chassis.moveToPoint(-23.5, -24.5, 800, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    chassis.turnToPoint(0, 0, 800, {.forwards = false}, false);
    chassis.moveDistance(-18, 700, {.forwards = false}, false);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
    shotgun.move_velocity(25);
    pros::delay(1000);
    moveWithVoltage(25, 25);
    pros::delay(300);
    moveWithVoltage(-20, -20);
    shotgun.move(-70);
    pros::delay(700);
    moveWithVoltage(0, 0);
}

void soloSigAWP() {
    shotgunRS.reset_position();
    chassis.setPose(SoloSigStart);
    screenTaskRunning = false;
    drop.toggle();
    Intake();
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);

    //preload
    // chassis.moveDistance(14, 450, {}, false);
    // pros::delay(100);

    //matchload
    chassis.moveToPoint(47.2, -48, 900, {.forwards = false, .maxSpeed = 85, .maxAngularSpeed = 10}, false);
    pros::delay(50);
    chassis.turnToPoint(47.5, -72, 550, {}, false);
    matchloader.extend();
    pros::delay(150);
    moveWithVoltage(60, 60);
    pros::delay(400);
    moveWithVoltage(40, 40);
    pros::delay(750);

    // right long goal
    chassis.moveToPoint(48.5, -27, 700, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    Score(50);
    moveWithVoltage(-50, -50);
    pros::delay(600);


    armMoving = false;
    stopIntaking();
    matchloader.retract();

    // both 3 stacks
    chassis.moveDistance(10, 500, {}, false);
    resetArm();
    chassis.turnToPoint(24, -24, 580, {}, false);
    Intake();
    chassis.moveDistance(18, 800, {.minSpeed = 35, .earlyExitRange = 5.5}, false);
    stopArm();
    moveWithVoltage(35, 35);
    pros::delay(300);
    moveWithVoltage(30, 60);
    pros::delay(300);
    matchloader.extend();
    drop.toggle();
    pros::delay(200);
    chassis.turnToPoint(-24, -24, 500, {}, false);
    matchloader.retract();
    shotgun.move(-55);
    chassis.moveToPoint(-17, -24, 1050, {.maxSpeed = 75, .maxAngularSpeed = 5, .minSpeed = 40, .earlyExitRange = 6});
    // chassis.moveToPose(-20, -24, -90, 1800, {.lead = 0.35, .minSpeed = 40, .U30 = false});

    chassis.waitUntilDone();
    moveWithVoltage(32, 32);
    pros::delay(200);
    matchloader.extend();
    pros::delay(300);

    // score on mid goal
    chassis.turnToPoint(-5, -5, 500, {.forwards = false}, false);
    chassis.moveDistance(-20, 640, {.forwards = false}, false);
    Score(25);
    int timeout = 0;
    while (shotgunRS.get_position() < 7700 && timeout < 600) {
        pros::delay(10);
        timeout +=10;
        printf("lever pos: %f\n", shotgunRS.get_position()/100.0f);
    }
    resetArm();
    intake.move(-128);
    pros::delay(450);
    drop.toggle();
    stopIntaking();
    chassis.moveToPoint(-48, -48, 950, {}, false);
    stopArm();
    chassis.turnToPoint(-47.5, -72, 550, {}, false);
    Intake();
    chassis.moveDistance(20, 620, {.maxSpeed = 62}, false);
    moveWithVoltage(40, 40);
    pros::delay(500);
    chassis.turnToPoint(-48.5, -24, 500, {.forwards = false}, false);
    chassis.moveToPoint(-48.3, -27, 700, {.forwards = false, .maxSpeed = 100, .maxAngularSpeed = 10}, false);
    Score(55);
    moveWithVoltage(-50, -50);
    pros::delay(550);
    stopIntaking();
    matchloader.retract();
    stopArm();
}

void test() {
 chassis.setPose(0, 0, 0);
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
    screenTaskRunning = false;
    pros::lcd::clear();
    pros::lcd::set_text(0, "Distance X Left Test");
    // pros::delay(4000);
    while(true) {
        pros::delay(10);
        pros::lcd::print(0, "X: %.4f", distanceResetX(false, 0)); // x
    }
}

void pidTest() {
    // chassis.setPose(0, 0, 0);
    // chassis.turnToHeading(90, 700, {}, false);
    // pros::delay(1000);
    // chassis.setPose(0, 0, 0);
    // chassis.turnToHeading(60, 700, {}, false);
    // pros::delay(1000);
    // chassis.setPose(0, 0, 0);
    // chassis.turnToHeading(45, 700, {}, false);
    // pros::delay(1000);
    // chassis.setPose(0, 0, 0);
    // chassis.turnToHeading(120, 800, {}, false);
    // pros::delay(1000);
    // chassis.setPose(0, 0, 0);
    // chassis.turnToHeading(150, 800, {}, false);
    // pros::delay(1000);
    // chassis.setPose(0, 0, 0);
    // chassis.turnToHeading(180, 1000, {}, false);
    // pros::delay(1000);
    // chassis.setPose(0, 0, 0);
    // pros::lcd::print(1, "Final Heading: %f", imu.get_heading());
    // printf("heading: %f\n", imu.get_heading());

    chassis.setPose(0, 0, 0);
    chassis.moveDistance(5, 700, {}, false);
    pros::delay(2000);
    chassis.setPose(0, 0, 0);
    chassis.moveDistance(12, 700, {}, false);
    pros::delay(2000);
    chassis.setPose(0, 0, 0);
    chassis.moveDistance(24, 800, {}, false);
    pros::delay(2000);
    chassis.setPose(0, 0, 0);
    chassis.moveDistance(36, 900, {}, false);
    pros::delay(2000);

    // chassis.setPose(0, 0, 0);
    // chassis.turnToHeading(5, 500, {}, false);
    // pros::delay(1000);
    // chassis.setPose(0, 0, 0);
    // chassis.turnToHeading(10, 500, {}, false);
    // pros::delay(1000);
    // chassis.setPose(0, 0, 0);
    // chassis.turnToHeading(20, 600, {}, false);
    // pros::delay(1000);
    // chassis.setPose(0, 0, 0);
    // chassis.turnToHeading(30, 600, {}, false);
    // pros::delay(1000);
}


// vector of tuple of function description and pointers
std::vector<std::tuple<std::string, void(*)()>> autons = {
    {"right bonus", rightBonus}, // 0
    {"left bonus", leftBonus},
    {"left AWP", leftAWP}, // 1
    {"right AWP", rightAWP}, // 2
    {"solo sig AWP", soloSigAWP}, // 3
    {"skills", skills}, // 4


    {"pid test", test}


};

