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

        virtual void write(const std::string &text) = 0;
        virtual std::string read() const = 0;

        friend class Robot;
    };
}

#endif
