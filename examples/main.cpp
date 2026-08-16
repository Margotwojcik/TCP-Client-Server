#include "Server.hpp"

#include <iostream>
#include <string>

int main() {
    try {
        Server server(8080);

        server.start();

        std::string message = server.receiveMessage();
        std::cout << "Received: " << message << '\n';

        server.sendMessage("Hello Client!");
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}