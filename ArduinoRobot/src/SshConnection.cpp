#include "SshConnection.h"

#include <libssh/libsshpp.hpp>
#include <vector>

namespace Arduino
{

    SshConnection::SshConnection(const std::string &hostName,
        const std::string &login, const std::string &password) :
    session(new ssh::Session())
    {
        session->setOption(SSH_OPTIONS_HOST, hostName.c_str());
        session->setOption(SSH_OPTIONS_USER, login.c_str());
        session->setOption(SSH_OPTIONS_PORT, 22);
        session->connect();
        session->userauthPassword(password.c_str());

        channel.reset(new ssh::Channel(*session));
    }

    void SshConnection::send(const std::string &command)
    {
        channel->openSession();
        channel->requestExec(command.c_str());
    }

    std::future<std::string> SshConnection::receive() const
    {
        channel->requestPty("xterm");
        channel->changePtySize(80, 25);
        channel->requestShell();
        ssh::Channel &rawChannel = *channel.get();
        return std::async(
            [&rawChannel]() -> std::string
            {
                std::string result;
                const size_t BUFFER_SIZE = 64;
                std::vector<char> buffer;
                buffer.reserve(BUFFER_SIZE);
                while(rawChannel.isOpen() && !rawChannel.isEof()) {
                    size_t bytesRead = rawChannel.read(&buffer, BUFFER_SIZE);
                    result.append(buffer.begin(), buffer.begin() + bytesRead);
                }
                rawChannel.close();
                return result;
            }
        );
    }

    SshConnection::~SshConnection()
    {
        session->disconnect();
    }

}
