#include "globals.hpp"
#include "lemlib/chassis/chassis.hpp"


void PIDLog() {

}

void moveDistance(int dist, int timeout, bool async) {
    bool forwards = (dist >= 0);
    float xtarget = chassis.getPose().x + dist * cos(chassis.getPose().theta);
    float ytarget = chassis.getPose().y + dist * sin(chassis.getPose().theta);
    chassis.moveToPoint(xtarget, ytarget, timeout, {.forwards = forwards}, async);
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
