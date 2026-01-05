#include "autons.h"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "globals.hpp"
#include <vector>
#include <tuple>
#include "pros/llemu.hpp" // IWYU pragma: keep
#include "pros/motors.h" // IWYU pragma: keep
#include "pros/rtos.hpp" // IWYU pragma: keep
#include <cstddef> // IWYU pragma: keep


// auton num
int autonIndex = 3;

extern bool screenTaskRunning;


lemlib::Pose origin(0, 0, 0);

lemlib::Pose RightStandardStart(17.3, -50.6, 14);
lemlib::Pose LeftStandardStart(-17.3, -50.6, -14);
lemlib::Pose SoloStart(-10, -45, 20);
lemlib::Pose SoloSigStart(-15, -48.5, -90);

void rightBonus() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    screenTaskRunning = false;
    chassis.setPose(RightStandardStart);
    Intake();
    chassis.moveDistance(18, 800, {.minSpeed = 35, .earlyExitRange = 7}, false);
    moveWithVoltage(30, 30);
    pros::delay(550);
    matchloader.extend();
    pros::delay(300);
    // chassis.moveDistance(-5, 500, {.forwards = false}, false);
    chassis.moveToPose(48, -72, 180, 2500, {.lead = 0.5, .maxSpeed = 80, .minSpeed = 45}, false);
    // chassis.turnToPoint(48, -52, 600, {}, false);
    // chassis.moveToPoint(48, -52, 900, {.maxAngularSpeed = 10}, false);
    // pros::lcd::print(2, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);

    // pros::delay(250);
    // pros::lcd::print(3, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);

    // chassis.turnToPoint(48, -72, 500, {}, false);
    // moveWithVoltage(80, 80);
    // pros::delay(300);
    // moveWithVoltage(40, 40);
    // pros::delay(700);
    chassis.turnToPoint(48, -24, 500, {.forwards = false}, false);
    shotgun.move(-64);
    pros::lcd::print(1, "x: %f, y: %f, t: %f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    chassis.moveToPoint(48, -27, 800, {.forwards = false, .maxSpeed = 80, .maxAngularSpeed = 15}, false);
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

void leftAWP() {
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
    screenTaskRunning = false;
    // chassis.setPose(LeftStandardStart);
    // Intake();
    // chassis.moveDistance(18, 800, {.minSpeed = 35, .earlyExitRange = 7}, false);
    // moveWithVoltage(20, 20);
    // pros::delay(550);
    // matchloader.extend();
    // pros::delay(300);
    // // chassis.moveDistance(-5, 500, {.forwards = false}, false);
    
    // chassis.turnToPoint(-5, -8, 600, {.forwards = false}, false);
    // drop.toggle();
    // chassis.moveDistance(-22, 800, {.forwards = false}, false);
    // shotgun.move_velocity(30);
    // matchloader.retract();
    // pros::delay(700);
    // shotgun.move(-60);
    // chassis.moveDistance(8, 600, {}, false);
    // shotgun.move(0);
    // chassis.moveToPose(-50, -6.5, -90, 2000, {.lead = 0.5});
    // chassis.waitUntil(26);
    // matchloader.extend();
    // chassis.waitUntilDone();
    // chassis.moveToPoint(-60, -24, 1000, {}, false);
    // drop.toggle();
    // chassis.moveToPose(-48, -72, 180, 2000, {.lead = 0.45, .maxSpeed = 100, .minSpeed = 40}, false);

    chassis.setPose(SoloSigStart);
    chassis.moveDistance(31, 800, {}, false);
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
    {"testing auto", test}, // 0
    {"pid test", pidTest}, // 1
    {"right bonus", rightBonus}, // 2
    {"left AWP", leftAWP} // 3
};

