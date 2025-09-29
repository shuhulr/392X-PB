#include "globals.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"


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

void LoadBag() {
    intake.move(128);
    fly.move(128);
}

void ScoreHigh() {
    intake.move(128);
    fly.move(128);
}

void StopAll() {
    intake.move(0);
    fly.move(0);
}
