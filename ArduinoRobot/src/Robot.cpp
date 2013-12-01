#include "Robot.h"

namespace Arduino
{
    Robot::Robot(const std::string &comPortName) :
        comPort(comPortName, std::ios::binary)
    {
    }

    void Robot::setControl(ControlType control)
    {
        comPort << static_cast<char>(control);
    }
}
