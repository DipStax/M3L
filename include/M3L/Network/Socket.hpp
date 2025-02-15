#pragma once

#include <array>
#include <limits>

#include "M3L/Network/BasicSocket.hpp"

#define DFT_SOCK_IMP_TOR(_p)                        \
    Socket() = default;                             \
    Socket(const Socket<T, _p> &&_is) noexcept      \
        : BaseSocket<T, _p>(std::move(_is)) {}      \
    Socket(const BaseSocket<T, _p> &&_bs) noexcept  \
        : BaseSocket<T, _p>(std::move(_bs)) {}      \
    virtual ~Socket() = default;

namespace m3l::net
{
    namespace imp
    {
        template<IsBaseIp T, Protocol _T>
        struct Socket;

        template<IsBaseIp T>
        struct Socket<T, Protocol::UDP> : public BasicSocket<T, Protocol::UDP>
        {
            DFT_SOCK_IMP_TOR(Protocol::UDP)

            [[nodiscard]] bool send(const uint8_t *_data, size_t _size);

            template<size_t _T = std::numeric_limit<size_t>::max()>
            [[nodiscard]] std::array<uint8_t, _T> receive();
        };

        template<IsBaseIp T>
        struct Socket<T, Protocol::TCP> : public BasicSocket<T, Protocol::TCP>
        {
            DFT_SOCK_IMP_TOR(Protocol::TCP)

            [[nodiscard]] bool send(const uint8_t* _data, size_t _size);

            template<size_t _T = std::numeric_limit<size_t>::max()>
            [[nodiscard]] std::array<uint8_t, _T> receive(RecvStrat _strat = RecvStrat::All);
        };
    }

    template<IsBaseIp T, Protocol _T>
    class Socket;

    template<IsBaseSocket T>
    struct Socket : public Socket<T::IpVersion, T::Protocol> {};

    template<IsBaseIp T, Protocol _T>
    class Socket : public imp::Socket<T, _T>
    {
        public:
            Socket() = default;
            Socket(const Ip<T> &_ip, uint32_t _port);
            Socket(const Socket<T, _T> &&_socket) noexcept;
            Socket(const BaseSocket<T, _T> &&_bs) noexcept;
            ~Socket() = default;

            void connect(const Ip<T> &_ip, uint32_t _port);
    };
}

#include "M3L/Network/Socket.inl"