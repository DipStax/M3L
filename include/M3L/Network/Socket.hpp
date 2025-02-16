#pragma once

#include <array>
#include <limits>

#include "M3L/Network/BasicSocket.hpp"

#define DFT_SOCK_IMP_TOR(_p)                        \
    Socket() = default;                             \
    Socket(const Socket<T, _p> &&_is) noexcept      \
        : BasicSocket<T, _p>(std::move(_is)) {}     \
    Socket(const BasicSocket<T, _p> &&_bs) noexcept \
        : BasicSocket<T, _p>(std::move(_bs)) {}     \
    virtual ~Socket() = default;

namespace m3l::net
{
    namespace imp
    {
        template<IsBaseIp T, Protocol _T>
        struct Socket;

        template<IsBaseIp T>
        class Socket<T, Protocol::UDP> : public BasicSocket<T, Protocol::UDP>
        {
            public:
                DFT_SOCK_IMP_TOR(Protocol::UDP)

                [[nodiscard]] bool send(const uint8_t *_data, size_t _size);

                template<size_t _T>
                [[nodiscard]] std::array<uint8_t, _T> receive();
        };

        template<IsBaseIp T>
        class Socket<T, Protocol::TCP> : public BasicSocket<T, Protocol::TCP>
        {
            public:
                DFT_SOCK_IMP_TOR(Protocol::TCP)

                [[nodiscard]] bool send(const uint8_t* _data, size_t _size);

                template<size_t _T>
                [[nodiscard]] std::array<uint8_t, _T> receive(RecvStrat _strat = RecvStrat::All);
        };
    }

    template<IsBaseIp T, Protocol _T>
    class Socket : public imp::Socket<T, _T>
    {
        public:
            Socket() = default;
            Socket(const Ip<T> &_ip, uint32_t _port);
            Socket(const Socket<T, _T> &&_socket) noexcept;
            Socket(const BasicSocket<T, _T> &&_bs) noexcept;
            ~Socket() = default;

            [[nodiscard]] bool connect(const Ip<T>& _ip, uint32_t _port);
    };

    //template<IsBaseSocket T>
    //class Socket : public Socket<typename T::IpVersion, decltype(T::Protocol)> {};
}

#include "M3L/Network/Socket.inl"