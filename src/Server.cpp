#include "Server.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

Server::Server(std::uint16_t port)
    : port_(port), serverSocket_(-1), clientSocket_(-1) {}

Server::~Server() {
#ifdef _WIN32
    if (clientSocket_ != INVALID_SOCKET) {
        closesocket(clientSocket_);
    }

    if (serverSocket_ != INVALID_SOCKET) {
        closesocket(serverSocket_);
    }

    WSACleanup();
#else
    if (clientSocket_ != -1) {
        close(clientSocket_);
    }

    if (serverSocket_ != -1) {
        close(serverSocket_);
    }
#endif
}

void Server::start() {
#ifdef _WIN32
    // Winsock musi zostać zainicjalizowany przed użyciem socketów.
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("WSAStartup failed");
    }
#endif

    // Tworzymy gniazdo TCP.
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);

#ifdef _WIN32
    if (serverSocket_ == INVALID_SOCKET) {
#else
    if (serverSocket_ == -1) {
#endif
        throw std::runtime_error("Failed to create socket");
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port_);

    // Przypisujemy socket do adresu i portu.
    if (bind(
            serverSocket_,
            reinterpret_cast<sockaddr*>(&address),
            sizeof(address)) == -1) {
        throw std::runtime_error("Failed to bind socket");
    }

    // Rozpoczynamy nasłuchiwanie na połączenia.
    if (listen(serverSocket_, 5) == -1) {
        throw std::runtime_error("Failed to listen on socket");
    }

    std::cout << "Server listening on port "
              << port_ << '\n';

    // Oczekujemy na połączenie klienta
    clientSocket_ = accept(
        serverSocket_,
        nullptr,
        nullptr);

#ifdef _WIN32
    if (clientSocket_ == INVALID_SOCKET) {
#else
    if (clientSocket_ == -1) {
#endif
        throw std::runtime_error("Failed to accept connection");
    }

    std::cout << "Client connected.\n";
}

std::string Server::receiveMessage() {
    char buffer[1024]{};

    int bytesReceived = recv(
        clientSocket_,
        buffer,
        sizeof(buffer) - 1,
        0);

    if (bytesReceived <= 0) {
        throw std::runtime_error("Failed to receive message");
    }

    return std::string(buffer, bytesReceived);
}

void Server::sendMessage(const std::string& message) {
    int bytesSent = send(
        clientSocket_,
        message.c_str(),
        static_cast<int>(message.size()),
        0
    );

    if (bytesSent == -1) {
        throw std::runtime_error("Failed to send message");
    }

    std::cout << "Message sent: " << message << '\n';
}