#include "globals.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "pros/rtos.hpp"
#include <cstdio>

bool intaking = false;
bool flying = false;

pros::Task instigateTask([]() {});

void PIDLog() {

}

void turnToHeadingU30(float heading, int timeout, lemlib::TurnToHeadingParams params, bool async) {
    angularController.kP = 0;
    angularController.kI = 0;
    angularController.kD = 0;
    angularController.windupRange = 5;
    printf("\n CHANGED ANGULAR CONTROLLER");
    chassis.turnToHeading(heading, timeout, params, async);
    printf("\n %f", angularController.kP);
    angularController.kP = 1.62; // reset to default
    angularController.kI = 0.25;
    angularController.kD = 12;
    angularController.windupRange = 5;
}

void Intake() {
    intake.move(127);
    intaking = true;
    fly.move(0);
    flying = false;
}

void moveWithVoltage(int left, int right) {
    leftMotors.move_voltage(left * 12000 / 127);
    rightMotors.move_voltage(right * 12000 / 127);
}

void stopDrive() {
    leftMotors.move_voltage(0);
    rightMotors.move_voltage(0);
}

void stopIntaking() {
    intake.move(0);
    fly.move(0);
    intaking = false;
    flying = false;
}

void IntakeBoth() {
    intake.move(127);
    intaking = true;
    flying = true;
    fly.move(127);
}

void antijam() {
    while (true) {
        if ((intaking) && (intake.get_efficiency() < 7) && (intake.get_voltage() > 5000)) {
            intake.move(-127);
            pros::delay(200);
            intake.move(127);
        }
        pros::delay(20);
    }
}

void antijamFly() {
    while (true) {
        if ((flying) && (fly.get_efficiency() < 2) && (fly.get_voltage() > 3000)) {
            flying = false;
            fly.move(-127);
            pros::delay(200);
            fly.move(127);
            flying = true;
        }
        pros::delay(30);
    }
}
double distanceResetX() {
    double angleDistanceX = (distanceX.get() / 25.4) + 4.4;
    double finalDistanceX = angleDistanceX * cos(lemlib::degToRad(imu.get_heading() + 90));
    return fabs(finalDistanceX);
}

double distanceResetY() {
    double angleDistanceY = (distanceY.get()/ 25.4) - 1.6;
    double finalDistanceY = angleDistanceY * sin(lemlib::degToRad(imu.get_heading() + 90));
    return fabs(finalDistanceY);
}