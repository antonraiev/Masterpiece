#include "Robot.h"

#include <sstream>

namespace Arduino
{
    Robot::Robot(std::unique_ptr<IConnection> connection) :
        connection(std::move(connection))
    {
    }

    void Robot::setControl(ControlType control)
    {
        std::string robotCommand(1, static_cast<char>(control));
        std::stringstream command;
        command << "echo '" << robotCommand << "' > /dev/ttyACM0";
        std::string commandStr = command.str();
        connection->send(commandStr);
    }

    const std::string& Robot::getOutput()
    {
        return output.get();
    }

    void Robot::update()
    {
        output = connection->receive();
    }
}
