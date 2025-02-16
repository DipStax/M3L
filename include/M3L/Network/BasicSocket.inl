#include "M3L/Network/BasicSocket.hpp"

namespace m3l::net
{
    template<IsBaseIp T, Protocol _T>
    BasicSocket<T, _T>::~BasicSocket()
    {
        close();
    }

    template<IsBaseIp T, Protocol _T>
    bool BasicSocket<T, _T>::is_open() const
    {
        char buffer;

        return !(recv(m_socket, &buffer, 1, MSG_PEEK) == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK);
    }

    template<IsBaseIp T, Protocol _T>
    bool BasicSocket<T, _T>::close()
    {
        bool ok = c::Socket::close(m_socket);

        if (ok)
            m_socket = SOCKET_ERROR;
        return ok;
    }

    template<IsBaseIp T, Protocol _T>
    BasicSocket<T, _T>::BasicSocket(const BasicSocket<T, _T> &&_bs) noexcept
        : m_socket(std::move(_bs.m_socket)), m_addr(_bs.m_addr)
    {
    }

    template<IsBaseIp T, Protocol _T>
    BasicSocket<T, _T>::BasicSocket(WIN_SOCKET _socket, sockaddr_in _addr)
        : m_socket(_socket), m_addr(_addr)
    {
        // verify protocol and stuff...
    }

    template<IsBaseIp T, Protocol _T>
    int BasicSocket<T, _T>::retreive_port() const
    {
        if (!is_open()) {
            // throw
        }
        if (m_addr.sin_port == 0) {
            // retreive port
        }
        return m_addr.sin_port;
    }
}