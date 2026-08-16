#pragma once

#include <cstdint>
#include <string>

#ifdef _WIN32
#include <winsock2.h>
#endif

class Server {
public:
    explicit Server(std::uint16_t port);
    ~Server();

    // Uruchamia serwer i oczekuje na połączenie klienta.
    void start();

    // Odbiera wiadomość od klienta.
    std::string receiveMessage();

    void sendMessage(const std::string& message);

private:
    std::uint16_t port_;

#ifdef _WIN32
    SOCKET serverSocket_;
    SOCKET clientSocket_;
#else
    int serverSocket_;
    int clientSocket_;
#endif
};