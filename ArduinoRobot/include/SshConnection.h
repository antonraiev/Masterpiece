#ifndef SSH_COONECTION
#define SSH_CONNECTION

#include <string>
#include <memory>

#include "IConnection.h"

namespace ssh
{
    class Session;
    class Channel;
}

namespace Arduino
{
    class SshConnection : public IConnection
    {
    public:
        SshConnection(const std::string &hostName, const std::string &login,
            const std::string &password);
        ~SshConnection();

        void send(const std::string &command) override;
        std::future<std::string> receive() const override;
    private:
        std::unique_ptr<ssh::Session> session;
        std::unique_ptr<ssh::Channel> channel;
    };
}

#endif
