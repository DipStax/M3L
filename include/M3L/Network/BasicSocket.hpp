#pragma once

#include "M3L/Network/Ip.hpp"
#include "M3L/Network/Protocol.hpp"

namespace m3l::net
{
    template<IsBaseIp T, Protocol _T>
    class BasicSocket
    {
        public:
            using IpVersion = T;
            constexpr Protocol Protocol = _T;

            virtual ~BasicSocket();

            [[nodiscard]] bool is_open() const;

            bool close();

        protected:
            BasicSocket() = default;
            BasicSocket(const BasicSocket &&_bs) noexcept;
            BasicSocket(WIN_SOCKET _socket, sockaddr_in _addr);

            int retreive_port();

            sockaddr_in m_addr{};
            WIN_SOCKET m_socket = SOCKET_ERROR;
    };
}

#include "M3L/Network/BasicSocket.inl"