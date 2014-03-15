#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <memory>
#include <future>

#include "IConnection.h"
#include "Sensor.h"

namespace Arduino
{
enum ControlType
{
  MOVE_FORWARD_SLOW     = 'S',
  MOVE_FORWARD_AVERAGE  = '8',
  MOVE_FORWARD_FAST     = 'F',
  MOVE_BACKWARD_SLOW    = 's',
  MOVE_BACKWARD_AVERAGE = '2',
  MOVE_BACKWARD_FAST    = 'f',
  MOVE_RIGHT            = '4',
  MOVE_LEFT             = '6',
  MOVE_STOP             = '5',
};


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