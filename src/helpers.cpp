#include "globals.hpp"


void PIDLog(){

}

void moveDistance(int dist, int timeout, bool async) {
    bool forwards = (dist >= 0);
    chassis.moveToPoint(chassis.getPose().x, dist, timeout, {.forwards = forwards}, async);
}
