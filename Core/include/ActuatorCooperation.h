#ifndef ACTUATOR_COOPERATION_H
#define ACTUATOR_COOPERATION_H

#include <vector>

#include "ActuatorCircle.h"

namespace Core
{

    class ActuatorCooperation
    {
    public:
        explicit ActuatorCooperation(
            double circleDiff,
            size_t positiveActuatorCount,
            size_t negativeActuatorCount,
            size_t startDelay = 1,
            size_t stopDelay = 2
        );
        
        size_t getCircleCount() const;
        ActuatorCircle& getPositiveCircle(size_t circleIndex);
        ActuatorCircle& getNegativeCircle(size_t circleIndex);

        void update(double alpha);
        int getControl() const;

    private:
        std::mt19937 mersenneTwisterEngine;

        size_t circleCount;
        std::vector<ActuatorCircle> positiveCircles;
        std::vector<ActuatorCircle> negativeCircles;
    };
}

#endif
