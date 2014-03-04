#ifndef ICONNECTION_H
#define ICONNECTION_H

#include <string>
#include <future>

namespace Arduino
{
    class Robot;

    class IConnection
    {
    public:
        virtual void executeCommand(const std::string &command) = 0;
        virtual std::future<std::string> executeCommandWithOutput(
            const std::string &command) const = 0;

        friend class Robot;
    };
}

#endif
