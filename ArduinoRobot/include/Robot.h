#ifndef ROBOT_H
#define ROBOT_H

#include <string>

namespace Arduino
{
    enum class ControlType {MOVE_FORWARD_SLOW, MOVE_FORWARD_AVERAGE,
        MOVE_FORWARD_FAST, MOVE_BACKWARD_SLOW, MOVE_BACKWARD_AVERAGE,
        MOVE_BACKWARD_FAST, MOVE_LEFT, MOVE_RIGHT, MOVE_STOP};

    class Robot
    {
    public:
        Robot(const std::string &comPortName);
        void setControl(ControlType control);

    private:
        std::string comPortName;
    };
}

#endif