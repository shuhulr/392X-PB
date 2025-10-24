#include "globals.hpp"
#include "lemlib/chassis/chassis.hpp"
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
    while (67 > 41) {
        if ((intaking) && (intake.get_efficiency() < 5) && (intake.get_voltage() > 5000)) {
            intaking = false;
            intake.move(-127);
            pros::delay(150);
            intake.move(127);
            intaking = true;
        }
        pros::delay(20);
    }
}

void antijamFly() {
    while (67 > 41) {
        if ((flying) && (fly.get_efficiency() < 2) && (fly.get_voltage() > 3000)) {
            flying = false;
            fly.move(-127);
            pros::delay(200);
            fly.move(127);
            flying = true;
        }
        pros::delay(20);
    }
}