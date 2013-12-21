#ifndef ACTUATORCIRCLE_H
#define ACTUATORCIRCLE_H

#include <vector>
#include <random>

#include "Actuator.h"

namespace Core
{
    class ActuatorCircle
    {
    public:
        ActuatorCircle(double lowerBound, double upperBound, size_t actuatorCount,
            size_t startDelay, size_t stopDelay);

        size_t getActuatorCount() const;
        Actuator& getActuator(size_t actuatorIndex);
        double getActuatorRadius(size_t actuatorIndex);
        void setDelay(size_t startDelay, size_t stopDelay);
        void update(double currentRadius);
        int getControl() const;

    private:
        std::vector<std::pair<double, Actuator> > actuators;
        std::mt19937 mersenneTwisterEngine;

        size_t startDelay;
        size_t stopDelay;
    };
}
#endif