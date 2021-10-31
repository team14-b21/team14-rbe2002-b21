#pragma once

#include "Chassis.h"
#include "PIDcontroller.h"
#include "DistanceSensor.h"

class StandoffController
{
private:
    PIDController pid;
    float leftEffort = 0, rightEffort = 0;
public:
    StandoffController(float Kp);

    void setTarget(float distance);
    void process(float reading);

    float l() {return leftEffort;}
    float r() {return rightEffort;}
};