#include "autons.h"
#include "lemlib/pose.hpp"


lemlib::Pose origin(0, 0, 0);

void auton1(lemlib::Chassis& chassis) {
    chassis.setPose(origin);
    chassis.turnToHeading(90, 5000, {}, false);
}