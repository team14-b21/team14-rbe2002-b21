#include "StandoffController.h"

StandoffController::StandoffController(): pid(PIDController(1)) {};

void StandoffController::setTarget(float target) {
    pid.setTarget(target);
}

void StandoffController::process(float current) {
    leftEffort = rightEffort = pid.CalcEffort(current);
}
