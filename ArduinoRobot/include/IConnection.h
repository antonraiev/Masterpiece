#ifndef ICONNECTION_H
#define ICONNECTION_H

#include <string>
#include <future>

namespace Arduino
{
    class Robot;

    class IConnection
    {
    protected:
        virtual void send(const std::string &command) = 0;
        virtual std::future<std::string> receive() const = 0;

        friend class Robot;
    };
}

#endif
