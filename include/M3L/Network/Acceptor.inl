#include "M3L/Network/Acceptor.hpp"

namespace m3l::net
{
    template<IsBaseIp T, Protocol _T>
    Acceptor<T, _T>::Acceptor(Ip<T> _ip, uint32_t _port)
        : Acceptor<T, _T>()
    {
        bind(_ip, _port);
    }

    template<IsBaseIp T, Protocol _T>
    bool Acceptor<T, _T>::bind(Ip<T> _ip, uint32_t _port)
    {
        extstd::Expected<sockaddr_in, int> error = c::Socket::bind<Ip<T>>(m_socket, _ip, _port);

        if (error)
            return false;
        m_addr = error.result();
        m_addr.sin_port = retreive_port();
        return true;
    }

    template<IsBaseIp T, Protocol _T>
    bool Acceptor<T, _T>::listen(int _max)
    {
        if (m_addr.sin_port == 0)
            return false;
        return ::listen(m_socket, _max) == 0;
    }

    template<IsBaseIp T, Protocol _T>
    Acceptor<T, _T>::BasicSocketType Acceptor<T, _T>::accept()
    {
        sockaddr_in addr{};
        int len = sizeof(sockaddr_in);
        WIN_SOCKET socket = ::accept(m_socket, &addr, &len);

        return BasicSocketType{ socket, addr };
    }
}