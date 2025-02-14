#pragma once

#include <array>

#include "M3L/Network/BasicSocket.hpp"

namespace m3l::net
{
    namespace imp
    {
        template<IsBaseIp T, prot _T>
        struct Socket;

        #define DFT_SOCK_IMP_TOR                            \
            Socket() = default;                             \
            Socket(const Socket<T> &&_is) noexcept          \
                : BaseSocket<T, _T>(std::move(_is)) {}      \
                                                            \
            Socket(const BaseSocket<T, _T> &&_bs) noexcept  \
                : BaseSocket<T, _T>(std::move(_bs)) {}      \
            virtual ~Socket() = default;

        template<IsBaseIp T>
        struct Socket<T, ::m3l::net::prot::UDP> : public BaseSocket<T, ::m3l::net::prot::UDP>
        {
            DFT_SOCK_IMP_TOR

            [[nodiscard]] bool send(const uint8_t *_data, size_t _size);

            template<size_t _T = std::numeric_limit<size_t>::max()>
            [[nodiscard]] std::array<uint8_t, _T> receive();
        };

        template<IsBaseIp T>
        struct Socket<T, ::m3l::net::prot::TCP> : public BaseSocket<T, ::m3l::net::prot::TCP>
        {
            DFT_SOCK_IMP_TOR

            [[nodiscard]] bool send(const std::vector<uint8_t> _data);

            template<size_t _T = std::numeric_limit<size_t>::max()>
            [[nodiscard]] std::array<uint8_t, _T> receive(RecvStrat _strat = RecvStrat::All);
        };
    }

    template<IsBaseSocket T>
    class Socket : public Socket<T::IpVersion, T::Protocol> {};

    template<IsBaseIp T, prot _T>
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