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
            static constexpr Protocol Protocol = _T;

            virtual ~BasicSocket();

            [[nodiscard]] bool is_open() const;

            bool close();

            static BasicSocket<T, _T> create(WIN_SOCKET _socket, sockaddr_in _addr);

        protected:
            BasicSocket() = default;
            BasicSocket(const BasicSocket<T, _T> &&_bs) noexcept;
            BasicSocket(WIN_SOCKET _socket, sockaddr_in _addr);

            int retreive_port() const;

            sockaddr_in m_addr{};
            WIN_SOCKET m_socket = SOCKET_ERROR;
    };
}

#include "M3L/Network/BasicSocket.inl"