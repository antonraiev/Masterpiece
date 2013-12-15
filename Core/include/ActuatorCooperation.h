#ifndef ACTUATOR_COOPERATION_H
#define ACTUATOR_COOPERATION_H

#include <vector>

#include "Actuator.h"

namespace Core
{
    struct Semicircle
    {
        double lowerBound;
        double upperBound;
    };

    class ActuatorCooperation
    {
    public:
        explicit ActuatorCooperation(double circleDiff, size_t actuatorCount,
            size_t actuatorStartDelay, size_t actuatorStopDelay);
        size_t getCircleCount() const;

        const Semicircle& getPositiveCircle(size_t circleIndex) const;
        const Semicircle& getNegativeCircle(size_t circleIndex) const;

        size_t getPositiveActuatorCount(size_t circleIndex) const;
        size_t getNegativeActuatorCount(size_t circleIndex) const;

        Actuator& getPositiveActuator(size_t circleIndex, size_t actuatorIndex);
        Actuator& getNegativeActuator(size_t circleIndex, size_t actuatorIndex);

        void update(double alpha);
        int getControl() const;

    private:
        std::vector<std::pair<Semicircle, std::vector<Actuator> > > positiveActuators;
        std::vector<std::pair<Semicircle, std::vector<Actuator> > > negativeActuators;
    };
}

#endif
