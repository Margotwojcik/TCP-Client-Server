#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <mutex>

class Server {
public:
    explicit Server(std::uint16_t port);
    ~Server();

    void start();
    void run();

    std::string receiveMessage();
    void sendMessage(const std::string& message);

private:
    void removeClient(int clientSocket);
    void handleClient(int clientSocket);
    void broadcastMessage(
        const std::string& message,
        int senderSocket);

    std::uint16_t port_;
    int serverSocket_;
    int clientSocket_;

    std::vector<int> clients_;
    std::mutex clientsMutex_;
};