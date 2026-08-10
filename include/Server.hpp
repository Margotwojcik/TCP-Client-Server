#pragma once

#include <cstdint>

class Server {
public:
    explicit Server(std::uint16_t port);
    ~Server();

    // Uruchamia serwer i oczekuje na połączenie klienta.
    void start();

private:
    std::uint16_t port_;
    int serverSocket_;
};