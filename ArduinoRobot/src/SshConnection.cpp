#include "SshConnection.h"

#define LIBSSH_STATIC 1

#include <libssh/libsshpp.hpp>

namespace Arduino
{

    SshConnection::SshConnection(
        const std::string &hostName,
        const std::string &login,
        const std::string &password)
         :
        session(new ssh::Session()),
        shellChannel(new ssh::Channel(*session.get()))
    {
        session->setOption(SSH_OPTIONS_HOST, hostName.c_str());
        session->setOption(SSH_OPTIONS_USER, login.c_str());
        session->connect();
        session->userauthPassword(password.c_str());

        shellChannel->openSession();
        shellChannel->requestPty("xterm", 80, 25);
        shellChannel->requestShell();
    }

    SshConnection::~SshConnection()
    {
        shellChannel->sendEof();
        shellChannel->close();

        session->disconnect();
    }

    void SshConnection::executeCommand(const std::string &command)
    {
        ssh::Channel commandChannel(*session.get());
        commandChannel.openSession();
        commandChannel.requestExec(command.c_str());
        commandChannel.sendEof();
        commandChannel.close();
    }

    void SshConnection::write(const std::string &text)
    {
        std::string textWithEndOfLine = text + "\r\n";
        shellChannel->write(textWithEndOfLine.c_str(), textWithEndOfLine.length());
    }

    std::string SshConnection::read() const
    {
        static const size_t BUFFER_SIZE = 64;
        char buffer[BUFFER_SIZE];

        std::string result;
        while(shellChannel->isOpen() && !shellChannel->isEof()) {
            size_t bytesRead = shellChannel->read(&buffer, BUFFER_SIZE);
            result.append(buffer, buffer + bytesRead);
        }

        return result;
    }
}
