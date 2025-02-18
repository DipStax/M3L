#include <thread>
#include <iostream>

#include "M3L/Network/Acceptor.hpp"
#include "M3L/Network/Socket.hpp"

#define PORT 8080

using TcpAcceptorV4 = m3l::net::Acceptor<
    m3l::net::ip::v4,
    m3l::net::Protocol::TCP
>;

using TcpSocketV4 = m3l::net::Socket<
    m3l::net::ip::v4,
    m3l::net::Protocol::TCP
>;

void server(bool& _listening, std::string _local_ip)
{
    TcpAcceptorV4 acceptor = TcpAcceptorV4{ m3l::net::Ip<m3l::net::ip::v4>(_local_ip), PORT };

    if (!acceptor.is_open()) {
        std::cout << "Client not connected to server" << std::endl;
        return;
    }
    acceptor.listen();
    std::cout << "Server listening" << std::endl;
    _listening = true;
    const uint8_t data[] = { 115, 101, 110, 100, 0 };

    TcpSocketV4 socket = TcpSocketV4{ std::move(acceptor.accept()) };
    std::cout << "Client connected to server (from server)" << std::endl;
    if (socket.send(data, 5)) {
        std::cout << "Error during data sending" << std::endl;
    }
    std::cout << "Server socket send package" << std::endl;
}

int main()
{
    WSADATA wsaData;
    int WSAResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (WSAResult != 0) {
        std::cout << "WSAStartup failed with error: " << WSAResult << std::endl;
        return 1;
    }

    std::string local_ip = "127.0.0.1";
    bool server_listen = false;
    std::thread server_thread{ server, std::ref(server_listen), local_ip };

    while (!server_listen) {}

    TcpSocketV4 client{ m3l::net::Ip<m3l::net::ip::v4>(local_ip), PORT };

    if (!client.is_open()) {
        std::cout << "Client not connected to server" << std::endl;
        return 1;
    }
    std::cout << "Client connected to server" << std::endl;

    std::array<uint8_t, 5> data = client.receive<5>();
    std::cout << "Received package: '";

    for (int i = 0; i < 5; i++)
        std::cout << static_cast<char>(data.at(i));
    std::cout << "'" << std::endl;

    while (!server_thread.joinable()) {}
    server_thread.join();
    std::cout << "Server thread joined" << std::endl;

    return 0;
}