#include "Actuator.h"

namespace Core
{
    Actuator::Actuator(size_t startDelay, size_t stopDelay) :
        startDelay(startDelay),
        stopDelay(stopDelay)
    {
        state = ActuatorState::REST;
    }

    void Actuator::setStartDelay(size_t startDelay)
    {
        this->startDelay = startDelay;
    }

    void Actuator::setStopDelay(size_t stopDelay)
    {
        this->stopDelay = stopDelay;
    }

    size_t Actuator::getStartDelay() const
    {
        return startDelay;
    }

    size_t Actuator::getStopDelay() const
    {
        return stopDelay;
    }

    size_t Actuator::getHeatingDelay() const
    {
        return heatingDelay;
    }

    size_t Actuator::getActiveDelay() const
    {
        return activeDelay;
    }

    ActuatorState Actuator::getState() const
    {
        return state;
    }

    bool Actuator::getControl() const
    {
        if(state == ActuatorState::ACTIVE) {
            return true;
        }
        return false;
    }

    void Actuator::update(double alpha)
    {
        switch(state)
        {
        case ActuatorState::REST:
            this->processRestState(alpha);
            break;

        case ActuatorState::HEATING:
            this->processHeatingState(alpha);
            break;
                
        case ActuatorState::ACTIVE:
            this->processActiveState(alpha);
            break;
        }
    }

    void Actuator::processRestState(double alpha)
    {
        if(alpha > 0) {
            heatingDelay = startDelay;
            state = ActuatorState::HEATING;
        }
    }

    void Actuator::processHeatingState(double alpha)
    {
        --heatingDelay;
        if(heatingDelay == 0) {
            activeDelay = stopDelay;
            state = ActuatorState::ACTIVE;
        }
    }

    void Actuator::processActiveState(double alpha)
    {
        if(alpha > 0) {
            activeDelay = stopDelay;
        } else {
            --activeDelay;
        }
        if(activeDelay == 0) {
            state = ActuatorState::REST;
        }
    }
}
