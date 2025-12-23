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
    shotgun.move(0);
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
    shotgun.move(0);
    intaking = false;
}

void antijam() {
    while (true) {
        if ((intaking) && (intake.get_efficiency() < 3) && (intake.get_voltage() > 5000)) {
            intake.move(-127);
            pros::delay(150);
            intake.move(127);
        }
        pros::delay(20);
    }
}


double distanceResetX() {
    double angleDistanceX = (distanceX.get() / 25.4) + 4.4;
    double finalDistanceX = angleDistanceX * cos(lemlib::degToRad(chassis.getPose().theta));
    return fabs(finalDistanceX);
}

double distanceResetX(int x, double heading) {
    double angleDistanceX = (x / 25.4) + 4.4;
    double finalDistanceX = angleDistanceX * cos(lemlib::degToRad(heading));
    return fabs(finalDistanceX);
}

double distanceResetY() {
    double angleDistanceY = (distanceY.get() / 25.4) + 4.8;
    double finalDistanceY = angleDistanceY * cos(lemlib::degToRad(chassis.getPose().theta));
    return fabs(finalDistanceY);
}

double distanceResetY(int y, double heading) {
    double angleDistanceY = (y / 25.4) + 4.8;
    double finalDistanceY = angleDistanceY * cos(lemlib::degToRad(heading));
    return fabs(finalDistanceY);
}