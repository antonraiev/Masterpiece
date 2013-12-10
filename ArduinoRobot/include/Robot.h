#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <memory>
#include <future>

#include "IConnection.h"

namespace Arduino
{
    enum class ControlType {MOVE_FORWARD_SLOW = 'S', MOVE_FORWARD_AVERAGE = 'A',
        MOVE_FORWARD_FAST = '8', MOVE_BACKWARD_SLOW = 's',
        MOVE_BACKWARD_AVERAGE = 'a', MOVE_BACKWARD_FAST = 'f', MOVE_LEFT = 'l',
        MOVE_RIGHT = 'r', MOVE_STOP = '5'};

    class Robot
    {
    public:
        Robot(std::unique_ptr<IConnection> connection);
        void setControl(ControlType control);
        const std::string& getOutput();
        void update();

    private:
        std::future<std::string> output;
        std::unique_ptr<IConnection> connection;
    };
}

#endif