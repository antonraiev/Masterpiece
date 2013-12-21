#include "ActuatorCircle.h"

#include <cassert>

namespace Core
{
    ActuatorCircle::ActuatorCircle(double lowerBound, double upperBound, size_t actuatorCount,
        size_t startDelay, size_t stopDelay)
    {
        assert(lowerBound <= upperBound && "Upper bound is greater than lower bound");

        this->setDelay(startDelay, stopDelay);
        mersenneTwisterEngine.seed(std::random_device()());
        double mean = lowerBound + (upperBound - lowerBound) / 2.f;
        double deviation = std::fabs(upperBound - lowerBound) / 8.f;
        std::normal_distribution<double> normalDistribution(mean, deviation);

        for(size_t i = 0; i < actuatorCount; ++i)
        {
            Actuator actuator(startDelay, stopDelay);
            double randomPosition = normalDistribution(mersenneTwisterEngine);
            actuators.push_back(std::make_pair(randomPosition, actuator));
        }
    }

    size_t ActuatorCircle::getActuatorCount() const
    {
        return actuators.size();
    }

    Actuator& ActuatorCircle::getActuator(size_t actuatorIndex)
    {
        return actuators[actuatorIndex].second;
    }

    double ActuatorCircle::getActuatorRadius(size_t actuatorIndex)
    {
        return actuators[actuatorIndex].first;
    }

    void ActuatorCircle::setDelay(size_t startDelay, size_t stopDelay)
    {
        this->startDelay = startDelay;
        this->stopDelay = stopDelay;
    }

    void ActuatorCircle::update(double currentRadius)
    {
        for(size_t i = 0; i < actuators.size(); ++i)
        {
            if(actuators[i].first <= currentRadius)
            {
                actuators[i].second.update(1);
            }
            else
            {
                actuators[i].second.update(-1);
            }
        }
    }

    int ActuatorCircle::getControl() const
    {
        int sum = 0;
        for(size_t i = 0; i < actuators.size(); ++i)
        {
            sum += actuators[i].second.getControl();
        }
        return sum;
    }
}
