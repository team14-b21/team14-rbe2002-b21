#include "StandoffController.h"

StandoffController::StandoffController(float Kp): pid(Kp) {};

void StandoffController::setTarget(float target) {
    pid.setTarget(target);
}

void StandoffController::process(float current) {
    leftEffort = rightEffort = pid.CalcEffort(current);
}
