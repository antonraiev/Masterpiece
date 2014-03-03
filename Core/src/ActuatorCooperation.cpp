#include "ActuatorCooperation.h"

#include <cstdlib>
#include <ctime>

namespace Core
{
    ActuatorCooperation::ActuatorCooperation(
        double circleDiff,
        size_t positiveActuatorCount,
        size_t negativeActuatorCount,
        size_t startDelay,
        size_t stopDelay
    )
    {
        circleCount = static_cast<size_t>(1 / circleDiff);

        for(size_t i = 0; i < circleCount; ++i) {
            double lowerBound = i * circleDiff;
            double upperBound = (i+1) * circleDiff;
            ActuatorCircle positiveCircle(lowerBound, upperBound, positiveActuatorCount,
                startDelay, stopDelay);
            positiveCircles.push_back(positiveCircle);
            ActuatorCircle negativeCircle(lowerBound, upperBound, negativeActuatorCount,
                startDelay, stopDelay);
            negativeCircles.push_back(negativeCircle);
        }
    }

    size_t ActuatorCooperation::getCircleCount() const
    {
        return circleCount;
    }

    ActuatorCircle& ActuatorCooperation::getPositiveCircle(size_t circleIndex)
    {
        return positiveCircles.at(circleIndex);
    }

    ActuatorCircle& ActuatorCooperation::getNegativeCircle(size_t circleIndex)
    {
        return negativeCircles.at(circleIndex);
    }

    void ActuatorCooperation::update(double alpha)
    {
        double positiveRadius = alpha >= 0 ? alpha : 0;
        double negativeRadius = alpha < 0 ? -alpha : 0;
        
        for(size_t i = 0; i < circleCount; ++i) {
            positiveCircles[i].update(positiveRadius);
            negativeCircles[i].update(negativeRadius);
        }
    }

    int ActuatorCooperation::getControl() const
    {
        int positiveSum = 0;
        int negativeSum = 0;

        for(size_t i = 0; i < circleCount; ++i) {
            positiveSum += positiveCircles[i].getControl();
            negativeSum += negativeCircles[i].getControl();
        }

        int result = positiveSum - negativeSum;
        return result > 0 ? result : 0;
    }
}
