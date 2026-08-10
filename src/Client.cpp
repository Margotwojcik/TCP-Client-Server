#include "Client.hpp"

#include <iostream>
#include <stdexcept>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

Client::Client(const std::string& address, std::uint16_t port)
    : address_(address), port_(port), clientSocket_(-1) {}

Client::~Client() {
#ifdef _WIN32
    if (clientSocket_ != -1) {
        closesocket(clientSocket_);
        WSACleanup();
    }
#else
    if (clientSocket_ != -1) {
        close(clientSocket_);
    }
#endif
}

void Client::connectToServer() {
#ifdef _WIN32
    // Inicjalizacja biblioteki Winsock
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("WSAStartup failed");
    }
#endif

    clientSocket_ = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket_ == -1) {
        throw std::runtime_error("Failed to create socket");
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port_);

    if (inet_pton(
            AF_INET,
            address_.c_str(),
            &serverAddress.sin_addr) <= 0) {
        throw std::runtime_error("Invalid server address");
    }

    // Nawiązujemy połączenie z serwerem
    if (connect(
            clientSocket_,
            reinterpret_cast<sockaddr*>(&serverAddress),
            sizeof(serverAddress)) == -1) {
        throw std::runtime_error("Failed to connect to server");
    }

    std::cout << "Connected to server.\n";
}

void Client::sendMessage(const std::string& message) {
    if (send(
            clientSocket_,
            message.c_str(),
            static_cast<int>(message.size()),
            0) == -1) {
        throw std::runtime_error("Failed to send message");
    }

    std::cout << "Message sent: " << message << '\n';
}