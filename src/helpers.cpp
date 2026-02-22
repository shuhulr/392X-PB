#include "globals.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "lemlib/pose.hpp"
#include "pros/rtos.hpp"
#include <cstdio>

bool intaking = false;
bool armMoving = false;


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
    intaking = false;
}

void Score(int speed) {
    shotgun.move_velocity(speed);
    armMoving = true;
}

void Score_S(int timeout) {
    float error = lemlib::angleError(108, shotgunRS.get_position()/100.0, false);
    int counter = 0;
    while(error > 5) {
        error = lemlib::angleError(108, shotgunRS.get_position()/100.0, false);
        shotgun.move(128 - (80/(1 + pow(2, 0.2*(error - 70) ) ) ) );
        pros::delay(10);
        counter += 10;
    }
}

void stopArm() {
    armMoving = false;
    shotgun.move(0);
}

void resetArm() {
    armMoving = false;
    shotgun.move(-70);
}
void resetArm(int voltage) {
    armMoving = false;
    shotgun.move(-voltage);
}

void antijamShotgun(int speed) {
    while (armMoving) {
        if ((shotgun.get_efficiency() < 3) && (shotgun.get_voltage() > 5000)) {
            shotgun.move(-127);
            pros::delay(60);
            shotgun.move_velocity(speed);
        }
        pros::delay(20);
    }
}


double distanceResetX(bool right, int wallOffset) {
    double angleDistanceX = (((right ? distanceXRight.get() : distanceXLeft.get()) + (right ? 3.1 : -3.1)*sin(lemlib::degToRad(chassis.getPose().theta))) / 25.4) + 5.1;
    double finalDistanceX = angleDistanceX * cos(lemlib::degToRad(chassis.getPose().theta + (right ? -wallOffset : wallOffset)));
    return fabs(finalDistanceX);
}

double distanceResetX(bool right, double x, double heading) {
    double angleDistanceX = ((right ? x - 3.1*sin(lemlib::degToRad(heading)) : x) / 25.4) + 4.1;
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