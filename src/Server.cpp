#include "Server.hpp"

#include <iostream>
#include <stdexcept>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

Server::Server(std::uint16_t port)
    : port_(port), serverSocket_(-1) {}

Server::~Server() {
#ifdef _WIN32
    if (serverSocket_ != -1) {
        closesocket(serverSocket_);
        WSACleanup();
    }
#else
    if (serverSocket_ != -1) {
        close(serverSocket_);
    }
#endif
}

void Server::start() {
#ifdef _WIN32
    // Winsock musi zostać zainicjalizowany przed użyciem socketów
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("WSAStartup failed");
    }
#endif

    // Tworzymy gniazdo TCP
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket_ == -1) {
        throw std::runtime_error("Failed to create socket");
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port_);

    // Przypisujemy socket do adresu i portu
    if (bind(
            serverSocket_,
            reinterpret_cast<sockaddr*>(&address),
            sizeof(address)) == -1) {
        throw std::runtime_error("Failed to bind socket");
    }

    // Rozpoczynamy nasłuchiwanie na połączenia
    if (listen(serverSocket_, 5) == -1) {
        throw std::runtime_error("Failed to listen on socket");
    }

    std::cout << "Server listening on port "
              << port_ << '\n';

    // accept() blokuje wykonanie do momentu połączenia klienta
#ifdef _WIN32
    SOCKET clientSocket = accept(
        serverSocket_, nullptr, nullptr);
#else
    int clientSocket = accept(
        serverSocket_, nullptr, nullptr);
#endif

    if (clientSocket == -1) {
        throw std::runtime_error("Failed to accept connection");
    }

    std::cout << "Client connected.\n";

#ifdef _WIN32
    closesocket(clientSocket);
#else
    close(clientSocket);
#endif
}