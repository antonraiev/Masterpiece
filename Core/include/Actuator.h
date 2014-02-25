#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <cstdlib>

namespace Core
{
    enum class ActuatorState {REST, HEATING, ACTIVE};

    class Actuator
    {
    public:
        Actuator(size_t startDelay, size_t stopDelay);

        void setStartDelay(size_t startDelay);
        void setStopDelay(size_t stopDelay);
        size_t getStartDelay() const;
        size_t getStopDelay() const;
        size_t getHeatingDelay() const;
        size_t getActiveDelay() const;
        ActuatorState getState() const;
        bool getControl() const;
        void update(double alpha);

    private:
        void processRestState(double alpha);
        void processHeatingState(double alpha);
        void processActiveState(double alpha);

    private:
        ActuatorState state;
        size_t startDelay;
        size_t stopDelay;
        
        size_t heatingDelay;
        size_t activeDelay;
    };
}

#endif
