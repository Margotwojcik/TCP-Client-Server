#pragma once

#include <cstdint>
#include <string>
#include <thread>

class Server {
public:
    explicit Server(std::uint16_t port);
    ~Server();

    void start();
    void run();

    std::string receiveMessage();
    void sendMessage(const std::string& message);

private:
    void handleClient();

    std::uint16_t port_;
    int serverSocket_;
    int clientSocket_;
};