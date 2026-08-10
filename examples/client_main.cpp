#include "Client.hpp"

#include <iostream>

int main() {
    try {
        Client client("127.0.0.1", 8080);

        client.connectToServer();
        client.sendMessage("Hello Server!");
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}