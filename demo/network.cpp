#include <thread>
#include <iostream>

#include "M3L/Network/Acceptor.hpp"

#define PORT 8080

using TcpAcceptorV4 = m3l::net::Acceptor<
    m3l::net::ip::v4,
    m3l::net::prot::TCP
>;

using TcpSocketV4 = m3l::net::Socket<TcpAcceptorV4::BasicSocketType>;

void server()
{
    TcpAcceptorV4 acceptor = TcpAcceptorV4{ m3l::net::Ip<m3l::net::ip::v4>{"127.0.0.1"}, PORT };
    acceptor.listen();

    TcpSocketV4 socket = TcpSocketV4{ std::move(acceptor.accept()) };
    socket.send([ 115, 101, 110, 100, 0 ], 5);
}

int main()
{
    std::thread server_thread{ server };

    TcpSocketV4 client{ m3l::net::Ip<m3l::net::ip::v4>{"127.0.0.1"}, PORT };
    {};

    if (!client.is_open()) {
        std::cout << "Client not connected to server" << std::endl;
        return 1;
    }

    std::array<uint8_t, 5> data = client.receive();

    while (!server_thread.joinable()) {}
    server_thread.join();
    return 0;
}