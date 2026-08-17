#include "Client.hpp"

#include <iostream>
#include <string>
#include <thread>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <unistd.h>
#endif

int main() {
    try {
        Client client("127.0.0.1", 8080);
        client.connectToServer();

        std::thread receiveThread(
            &Client::receiveMessages,
            &client);

        std::string message;

        while (true) {
            std::cout << "You: ";
            std::getline(std::cin, message);

            client.sendMessage(message);

            if (message == "/exit") {
                break;
            }
        }

#ifdef _WIN32
        shutdown(client.getSocket(), SD_BOTH);
#else
        shutdown(client.getSocket(), SHUT_RDWR);
#endif

        receiveThread.join();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}