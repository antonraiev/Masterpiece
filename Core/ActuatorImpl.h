#ifndef ACTUATORIMPL_H
#define ACTUATORIMPL_H

namespace Core
{
    enum class ActuatorState {REST, HEATING, ACTIVE};

    template <typename TControlType>
    class Actuator
    {
    public:
        Actuator(TControlType type, size_t startDelay, size_t stopDelay) :
            type(type),
            startDelay(startDelay),
            stopDelay(stopDelay)
        {
            state = ActuatorState::REST;
        }

        void setStartDelay(size_t startDelay)
        {
            this->startDelay = startDelay;
        }

        void setStopDelay(size_t stopDelay)
        {
            this->stopDelay = stopDelay;
        }

        size_t getStartDelay() const
        {
            return startDelay;
        }

        size_t getStopDelay() const
        {
            return stopDelay;
        }

        ActuatorState getState() const
        {
            return state;
        }

        bool getControl() const
        {
            if(state == ActuatorState::ACTIVE) {
                return true;
            }
            return false;
        }

        void update(double alpha)
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

    private:
        void processRestState(double alpha)
        {
            if(alpha > 0) {
                heatingDelay = startDelay;
                state = ActuatorState::HEATING;
            }
        }

        void processHeatingState(double alpha)
        {
            if(alpha > 0) {
                activeDelay = stopDelay;
            } else {
                --heatingDelay;
            }
            if(heatingDelay == 0) {
                activeDelay = stopDelay;
                state = ActuatorState::ACTIVE;
            }
        }

        void processActiveState(double alpha)
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

    private:
        TControlType type;
        ActuatorState state;
        size_t startDelay;
        size_t stopDelay;
        
        size_t heatingDelay;
        size_t activeDelay;
    };
}

#endif
