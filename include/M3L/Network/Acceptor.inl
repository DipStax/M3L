#include <iostream>

#include "M3L/Network/Acceptor.hpp"

namespace m3l::net
{
    template<IsBaseIp T, Protocol _T>
    Acceptor<T, _T>::Acceptor(Ip<T> _ip, uint32_t _port)
        : BasicSocket<T, _T>()
    {
        bind(_ip, _port);
    }

    template<IsBaseIp T, Protocol _T>
    bool Acceptor<T, _T>::bind(Ip<T> _ip, uint32_t _port)
    {
        std::cout << "Binding Acceptor to " << _ip << ":" << _port << std::endl;
        extstd::Expected<sockaddr_in, int> error = c::Socket::bind<Ip<T>>(this->m_socket, _ip, _port);

        if (error) {
            std::cout << "Bind error: " << error.error() << " => " << WSAGetLastError() << std::endl;
            return false;
        }
        this->m_addr = error.result();
        this->m_addr.sin_port = this->retreive_port();
        return true;
    }

    template<IsBaseIp T, Protocol _T>
    bool Acceptor<T, _T>::listen(int _max)
    {
        if (this->m_addr.sin_port == 0)
            return false;
        return ::listen(this->m_socket, _max) == 0;
    }

    template<IsBaseIp T, Protocol _T>
    Acceptor<T, _T>::BasicSocketType Acceptor<T, _T>::accept()
    {
        sockaddr_in addr{};
        int len = sizeof(sockaddr_in);
        WIN_SOCKET socket = ::accept(this->m_socket, reinterpret_cast<sockaddr *>(&addr), &len);

        return BasicSocket<T, _T>::create(socket, addr);
    }
}