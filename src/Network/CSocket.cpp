#include "M3L/Network/CSocket.hpp"

namespace m3l::net::c
{
    WIN_SOCKET Socket::create(int _dom, int _type, int _proto)
    {
        return socket(_dom, _type, _proto);
    }

    bool Socket::blocking(WIN_SOCKET _socket, bool _block)
    {
        return false;
    }

    bool Socket::close(WIN_SOCKET _socket)
    {
        return closesocket(_socket) == 0;
    }
}