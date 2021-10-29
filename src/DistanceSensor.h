#pragma once

class DistanceSensor
{
public:
    virtual bool getDistance(float& distance) = 0;
};
