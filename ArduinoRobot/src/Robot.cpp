#include "Robot.h"

#include <sstream>

namespace Arduino
{
    Robot::Robot(std::unique_ptr<IConnection> connection) :
        connection(std::move(connection))
    {
        this->connection->write("cat /dev/ttyACM0");
    }

    void Robot::setControl(ControlType control)
    {
        std::string robotCommand(1, static_cast<char>(control));
        std::stringstream commandStream;

        commandStream << "echo " << robotCommand << " > /dev/ttyACM0";
        std::string command = commandStream.str();

        connection->executeCommand(command);
    }

    const std::string& Robot::getOutput()
    {
        return connection->read();
    }

    void Robot::update()
    {
    }
}
