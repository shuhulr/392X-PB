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
int autonIndex = 2;

extern bool screenTaskRunning;


lemlib::Pose origin(0, 0, 0);

lemlib::Pose RightStandardStart(17.5, -50.3, 12);
lemlib::Pose LeftStandardStart(-17.5, -50.3, -12);
lemlib::Pose SoloStart(-10, -45, 20);
lemlib::Pose SoloSigStart(15.5, -48, 90);

void rightBonus() {
    chassis.setPose(RightStandardStart);
    Intake();
    chassis.moveDistance(26, 800, {});
    chassis.waitUntil(13);
    matchloader.extend();
    chassis.moveToPose(48, -72, 180, 2200, {.minSpeed = 40}, false);
    
}



void test() {
 chassis.setPose(SoloSigStart);
    //pros::delay(5000);
    printf("=== BEGIN DISTANCE SENSOR TEST ===\n");

    // Test 1: Ping Y sensor
    printf("Test 1: Reading Y...\n");
    int yVal = distanceY.get();
    printf("Y VALUE = %d\n", yVal);

    //pros::delay(10);

    // Test 2: Ping X sensor
    printf("Test 2: Reading X...\n");
    int xVal = distanceX.get();
    printf("X VALUE = %d\n", xVal);

    //pros::delay(10);

    printf("=== END TEST ===\n");


    printf("=== IMU TEST ===\n");
    printf("Calling imu.get_heading()...\n");
    pros::delay(200); 
    double h = imu.get_heading();
    printf("IMU HEADING = %f\n", h);
    printf("=== END IMU TEST ===\n");


    /*printf("\nodom pos\n");
    printf("X: %f\n", chassis.getPose().x);
    printf("Y: %f\n", chassis.getPose().y);
    printf("Theta: %f\n", chassis.getPose().theta);*/


    double angleDistanceX = (xVal / 25.4) + 4.4;

    double finalDistanceX = angleDistanceX * cos(lemlib::degToRad(imu.get_heading()));
    printf("finaldistx: %lf\n", finalDistanceX);
    double x = fabs(finalDistanceX);


    double angleDistanceY = (yVal / 25.4) + 4.8;
    double finalDistanceY = angleDistanceY * cos(lemlib::degToRad(imu.get_heading() ));
    printf("finaldisty: %lf\n", finalDistanceY);
    double y = fabs(finalDistanceY);
    pros::delay(500);

    chassis.setPose(72 - x, -(72 - y), imu.get_heading());

    printf("\n sensor pos\n");
    printf("X: %f\n", chassis.getPose().x);
    printf("Y: %f\n", chassis.getPose().y);
    printf("Theta: %f\n", chassis.getPose().theta);
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
    chassis.moveDistance(5, 1000, {}, false);
    pros::delay(2000);
    chassis.setPose(0, 0, 0);
    chassis.moveDistance(12, 1000, {}, false);
    pros::delay(2000);
    chassis.setPose(0, 0, 0);
    chassis.moveDistance(24, 1000, {}, false);
    pros::delay(2000);
    chassis.setPose(0, 0, 0);
    chassis.moveDistance(36, 1000, {}, false);
    pros::delay(2000);
}
// vector of tuple of function description and pointers
std::vector<std::tuple<std::string, void(*)()>> autons = {
    {"testing auto", test}, // 0
    {"pid test", pidTest}, // 1
    {"right bonus", rightBonus} // 2
};

