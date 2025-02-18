#include <ws2tcpip.h>

#include "M3L/Network/CSocket.hpp"
#include "Tool/Expected.hpp"

namespace m3l::net::c
{
    template<IsBaseIp T, Protocol _T>
    constexpr WIN_SOCKET Socket::create()
    {
        if constexpr (_T == Protocol::TCP) {
            return m3l::net::c::Socket::create(T::familly, SOCK_STREAM, IPPROTO_TCP);
        } else if constexpr (_T == Protocol::UDP) {
            return m3l::net::c::Socket::create(T::familly, SOCK_DGRAM, IPPROTO_UDP);
        }
    }

    template<IsIpFormat T>
    extstd::Expected<sockaddr_in, int> Socket::bind(WIN_SOCKET _socket, const T &_ip, uint32_t _port)
    {
        sockaddr_in addr{};
        int err = 0;

        addr.sin_family = T::familly;
        inet_pton(T::familly, _ip.str().c_str(), &(addr.sin_addr.s_addr));
        addr.sin_port = htons(_port);
        err = ::bind(_socket, reinterpret_cast<const sockaddr *>(&addr), sizeof(sockaddr_in));

        if (err == 0)
            return extstd::Expected<sockaddr_in, int>(addr);
        return extstd::Expected<sockaddr_in, int>(err);
    }
}