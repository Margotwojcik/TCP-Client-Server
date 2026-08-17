#include "Client.hpp"

#include <iostream>
#include <string>

int main() {
    try {
        Client client("127.0.0.1", 8080);
        client.connectToServer();

        std::string message;

        while (true) {
            std::cout << "You: ";
            std::getline(std::cin, message);

            client.sendMessage(message);

            if (message == "exit") {
                break;
            }

            std::string response = client.receiveMessage();
            std::cout << "Server: " << response << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}