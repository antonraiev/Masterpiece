#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <fstream>

namespace Arduino
{
    enum class ControlType {MOVE_FORWARD_SLOW = 'S', MOVE_FORWARD_AVERAGE = 'A',
        MOVE_FORWARD_FAST = 'F', MOVE_BACKWARD_SLOW = 's', 
        MOVE_BACKWARD_AVERAGE = 'a', MOVE_BACKWARD_FAST = 'f', MOVE_LEFT = 'l',
        MOVE_RIGHT = 'r', MOVE_STOP = 'x'};

    class Robot
    {
    public:
        Robot(const std::string &comPortName);
        void setControl(ControlType control);

    private:
        std::fstream comPort;
    };
}

#endif