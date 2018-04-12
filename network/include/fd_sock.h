#ifndef __FD_SOCK_H__
#define __FD_SOCK_H__

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdexcept>

namespace network {

constexpr int ERROR_STATE = -1;

template<int SDOMAIN, int STYPE, int SPROTO>
class SocketHolder
{
public:
    SocketHolder()
    : m_fd(socket(SDOMAIN, STYPE, SPROTO))
    {
        if (m_fd == ERROR_STATE)
        {
            throw std::runtime_error("Socket creation failed");
        }
    }

    SocketHolder(int fd)
    : m_fd(fd)
    {}

    int GetFD() const { return m_fd; }
    int GetErrno() const { return errno; }

    ~SocketHolder()
    {
        close(m_fd);
    }

private:
    int m_fd;
};

} // end of `network` namespace

#endif // __FD_SOCK_H__
