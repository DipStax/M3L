#include <ws2tcpip.h>

#include "M3L/Network/Socket.hpp"

namespace m3l::net
{
    namespace imp
    {
        template<IsBaseIp T>
        bool Socket<T, Protocol::UDP>::send(const uint8_t *_data, size_t _size)
        {
            return sendto(this->m_socket, _data, _size, 0, reinterpret_cast<sockaddr *>(this->m_addr), sizeof(sockaddr_in)) > 0;
        }

        template<IsBaseIp T>
        template<size_t _T>
        std::array<uint8_t, _T> Socket<T, Protocol::UDP>::receive()
        {
            std::array<uint8_t, _T> data;

            if (recvfrom(this->m_socket, data.data(), _T, 0, reinterpret_cast<sockaddr *>(&(this->m_addr)), sizeof(sockaddr_in)) == SOCKET_ERROR) {
                // throw exception
            }
            return data;
        }

        template<IsBaseIp T>
        bool Socket<T, Protocol::TCP>::send(const uint8_t *_data, size_t _size)
        {
            return ::send(this->m_socket, reinterpret_cast<const char*>(_data), static_cast<int>(_size), 0) > 0;
        }

        template<IsBaseIp T>
        template<size_t _T>
        std::array<uint8_t, _T> Socket<T, Protocol::TCP>::receive(RecvStrat _strat)
        {
            std::array<uint8_t, _T> data{};

            if (recv(this->m_socket, reinterpret_cast<char *>(data.data()), _T, _strat) == SOCKET_ERROR) {
                // throw exception
                std::cout << "error: " << WSAGetLastError() << std::endl;
                throw;
            }
            return data;
        }
    }

    template<IsBaseIp T, Protocol _T>
    Socket<T, _T>::Socket(const Ip<T> &_ip, uint32_t _port)
    {
        if (!connect(_ip, _port)) {
            throw;
        }
    }

    template<IsBaseIp T, Protocol _T>
    Socket<T, _T>::Socket(const Socket<T, _T> &&_socket) noexcept
        : imp::Socket<T, _T>(std::move(_socket))
    {
    }

    template<IsBaseIp T, Protocol _T>
    Socket<T, _T>::Socket(const BasicSocket<T, _T> &&_bs) noexcept
       : imp::Socket<T, _T>(std::move(_bs))
    {
    }

    template<IsBaseIp T, Protocol _T>
    bool Socket<T, _T>::connect(const Ip<T>& _ip, uint32_t _port)
    {
        this->m_addr.sin_family = T::familly;
        inet_pton(T::familly, _ip.str().c_str(), &(this->m_addr.sin_addr.s_addr));
        this->m_addr.sin_port = htons(_port);
        return ::connect(this->m_socket, reinterpret_cast<const sockaddr*>(&(this->m_addr)), sizeof(sockaddr_in)) == 0;
    }
}
