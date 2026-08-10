#include "Server.hpp"

#include <iostream>
#include <string>

int main() {
    try {
        Server server(8080);

        server.start();

        std::string message = server.receiveMessage();
        std::cout << "Received: " << message << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}