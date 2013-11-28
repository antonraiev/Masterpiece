#ifndef ROBOT_H
#define ROBOT_H

#include <string>

namespace Arduino
{
    class Robot
    {
    public:
        Robot(const std::string &comPort);
    };
}

#endif