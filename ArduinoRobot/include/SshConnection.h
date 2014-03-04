#ifndef SSH_COONECTION
#define SSH_CONNECTION

#include <string>
#include <memory>

#include "IConnection.h"

namespace ssh
{
    class Session;
}

namespace Arduino
{
    class SshConnection : public IConnection
    {
    public:
        SshConnection(const std::string &hostName, const std::string &login,
            const std::string &password);

        void executeCommand(const std::string &command) override;
        std::future<std::string> executeCommandWithOutput(
            const std::string &command) const override;
    private:
        std::unique_ptr<ssh::Session> session;

    };
}

#endif
