#pragma once

#include <cstdint>
#include <string>

#ifdef _WIN32
#include <winsock2.h>
#endif

class Client {
public:
    explicit Client(const std::string& address, std::uint16_t port);
    ~Client();

    void connectToServer();
    void sendMessage(const std::string& message);
    std::string receiveMessage();
    void receiveMessages();

    #ifdef _WIN32
    SOCKET getSocket() const;
#else
    int getSocket() const;
#endif

private:
    std::string address_;
    std::uint16_t port_;

#ifdef _WIN32
    SOCKET clientSocket_;
#else
    int clientSocket_;
#endif
};