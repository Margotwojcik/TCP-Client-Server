#include "Server.hpp"

#include <iostream>
#include <string>

int main() {
    try {
        Server server(8080);

        server.start();
        server.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}