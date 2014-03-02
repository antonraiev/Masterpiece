#include "SshConnection.h"

#define LIBSSH_STATIC 1

#include <libssh/libsshpp.hpp>

namespace Arduino
{

    SshConnection::SshConnection(const std::string &hostName,
        const std::string &login, const std::string &password) :
    session(new ssh::Session())
    {
        session->setOption(SSH_OPTIONS_HOST, hostName.c_str());
        session->setOption(SSH_OPTIONS_USER, login.c_str());
        session->connect();
        session->userauthPassword(password.c_str());
    }

    void SshConnection::executeCommand(const std::string &command)
    {
        ssh::Channel channel(*session);
        channel.openSession();
        channel.requestExec(command.c_str());
        channel.close();
        channel.sendEof();
    }

    std::future<std::string> SshConnection::executeCommandWithOutput(
        const std::string &command) const
    {
        static const size_t BUFFER_SIZE = 64;
        ssh::Session *rawSession = session.get();

        return std::async(
            [&command, rawSession]() -> std::string
            {
                std::unique_ptr<ssh::Channel> channel(
                    new ssh::Channel(*rawSession));
                channel->openSession();
                channel->requestExec(command.c_str());
                std::string result;
                char buffer[BUFFER_SIZE];
                while(channel->isOpen() && !channel->isEof()) {
                    size_t bytesRead = channel->read(&buffer, BUFFER_SIZE);
                    result.append(buffer, buffer + bytesRead);
                }
                channel->sendEof();
                channel->close();
                return result;
            }
        );
    }
}
