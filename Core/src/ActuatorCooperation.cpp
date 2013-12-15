#include "ActuatorCooperation.h"

#include <cstdlib>
#include <ctime>

namespace Core
{
    ActuatorCooperation::ActuatorCooperation(double circleDiff, size_t actuatorCount,
        size_t actuatorStartDelay, size_t actuatorStopDelay)
    {
        const int factor = 10;
        size_t positiveActuatorCount = actuatorCount;
        size_t negativeActuatorCount = actuatorCount / factor;

        const size_t circleCount = static_cast<size_t>(1 / circleDiff);
        for(int i = 0; i < circleCount; ++i)
        {
            Semicircle semicircle;
            semicircle.lowerBound = -i * circleDiff;
            semicircle.upperBound = -(i+1) * circleDiff;
            negativeActuators.push_back(std::make_pair(semicircle, std::vector<Actuator>()));
        }
        for(size_t i = 0; i < circleCount; ++i)
        {
            Semicircle semicircle;
            semicircle.lowerBound = i * circleDiff;
            semicircle.upperBound = (i+1) * circleDiff;
            positiveActuators.push_back(std::make_pair(semicircle, std::vector<Actuator>()));
        }

        srand(static_cast<size_t>(time(0)));
        for(size_t i = 0; i < negativeActuatorCount; ++i)
        {
            Actuator actuator(actuatorStartDelay, actuatorStopDelay);
            size_t circleIndex = rand() % negativeActuators.size();
            negativeActuators[circleIndex].second.push_back(actuator);
        }

        for(size_t i = 0; i < positiveActuatorCount; ++i)
        {
            Actuator actuator(actuatorStartDelay, actuatorStopDelay);
            size_t circleIndex = rand() % positiveActuators.size();
            positiveActuators[circleIndex].second.push_back(actuator);
        }
    }

    size_t ActuatorCooperation::getCircleCount() const
    {
        return negativeActuators.size();
    }

    const Semicircle& ActuatorCooperation::getPositiveCircle(size_t circleIndex) const
    {
        return positiveActuators[circleIndex].first;
    }

    const Semicircle& ActuatorCooperation::getNegativeCircle(size_t circleIndex) const
    {
        return negativeActuators[circleIndex].first;
    }

    size_t ActuatorCooperation::getPositiveActuatorCount(size_t circleIndex) const
    {
        return positiveActuators[circleIndex].second.size();
    }

    size_t ActuatorCooperation::getNegativeActuatorCount(size_t circleIndex) const
    {
        return negativeActuators[circleIndex].second.size();
    }

    Actuator& ActuatorCooperation::getPositiveActuator(size_t circleIndex, size_t actuatorIndex)
    {
        return positiveActuators[circleIndex].second[actuatorIndex];
    }

    Actuator& ActuatorCooperation::getNegativeActuator(size_t circleIndex, size_t actuatorIndex)
    {
        return negativeActuators[circleIndex].second[actuatorIndex];
    }

    void ActuatorCooperation::update(double alpha)
    {
        double positiveRadius = alpha >= 0 ? alpha : 0;
        double negativeRadius = alpha < 0 ? alpha : 0;

        for(size_t i = 0; i < negativeActuators.size(); ++i)
        {
            if(negativeActuators[i].first.upperBound >= negativeRadius)
            {
                for(size_t j = 0; j < negativeActuators[i].second.size(); ++j)
                {
                    negativeActuators[i].second[j].update(1);
                }
            }
            else 
            {
                for(size_t j = 0; j < negativeActuators[i].second.size(); ++j)
                {
                    negativeActuators[i].second[j].update(-1);
                }
            }
            if(positiveActuators[i].first.upperBound <= positiveRadius)
            {
                for(size_t j = 0; j < positiveActuators[i].second.size(); ++j)
                {
                    positiveActuators[i].second[j].update(1);
                }
            }
            else 
            {
                for(size_t j = 0; j < positiveActuators[i].second.size(); ++j)
                {
                    positiveActuators[i].second[j].update(-1);
                }
            }
        }
    }

    int ActuatorCooperation::getControl() const
    {
        int positiveSum = 0;
        int negativeSum = 0;

        for(size_t i = 0; i < negativeActuators.size(); ++i)
        {
            for(size_t j = 0; j < negativeActuators[i].second.size(); ++j)
            {
                negativeSum += negativeActuators[i].second[j].getControl();
            }
        }
        for(size_t i = 0; i < positiveActuators.size(); ++i)
        {
            for(size_t j = 0; j < positiveActuators[i].second.size(); ++j)
            {
                positiveSum += positiveActuators[i].second[j].getControl();
            }
        }

        int result = positiveSum - negativeSum;
        return result > 0 ? result : 0;
    }
}
