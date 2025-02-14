#include "M3L/Network/Socket.hpp"

namespace m3l::net
{
    namespace imp
    {
        template<IsBaseIp T>
        bool Socket<T, ::m3l::net::prot::UDP>::send(const uint8_t *_data, size_t _size)
        {
            return ::sendto(m_socket, _data, _size, 0, reinterpret_cast<sockaddr *>(m_addr), sizeof(sockaddr_in)) > 0;
        }

        template<IsBaseIp T>
        template<size_t _T = std::numeric_limit<size_t>::max()>
        std::array<uint8_t, _T> Socket<T, ::m3l::net::prot::TCP>::receive(RecvStrat _strat)
        {
            std::array<uint8_t, _T> data;

            if (recvfrom(m_socket, data.data(), _T, 0, reinterpret_cast<sockaddr *>(m_addr), sizeof(sockaddr_in)) == SOCKET_ERROR) {
                // throw exception
            }
            return data;
        }

        template<IsBaseIp T>
        bool Socket<T, ::m3l::net::prot::TCP>::send(const uint8_t *_data, size_t _size)
        {
            return ::send(m_socket, _data, _size, 0) > 0;
        }

        template<IsBaseIp T>
        template<size_t _T = std::numeric_limit<size_t>::max()>
        std::array<uint8_t, _T> Socket<T, ::m3l::net::prot::TCP>::receive(RecvStrat _strat)
        {
            std::array<uint8_t, _T> data;

            if (recv(m_socket, data.data(), _T, _strat) == SOCKET_ERROR) {
                // throw exception
            }
            return data;
        }
    }

    template<IsBaseIp T, prot _T>
    Socket<T, _T>::Socket(const Ip<T> &_ip, uint32_t _port);
    {
        connect(_ip, _port);
    }

    template<IsBaseIp T, prot _T>
    Socket<T, _T>::Socket(const Socket<T, _T> &&_socket) noexcept
        : imp::Socket<T, _T>(std::move(_socket))
    {
    }

    template<IsBaseIp T, prot _T>
    Socket<T, _T>::Socket(const BaseSocket<T, _T> &&_bs) noexcept;
       : imp::Socket<T, _T>(std::move(_bs))
    {
    }
}
