# TCP Client-Server

A multithreaded TCP client-server application written in C++ using TCP sockets and CMake.

## Features

- TCP client-server communication
- Multiple clients connected simultaneously
- Multithreaded server using `std::thread`
- Thread-safe client management using `std::mutex`
- Broadcasting messages between connected clients
- Separate client thread for receiving messages
- Graceful client disconnection using `/exit`
- Basic error handling
- Cross-platform socket structure for Windows and Linux

## Technologies

- C++
- TCP/IP
- Sockets
- Winsock2
- CMake
- MSVC
- `std::thread`
- `std::mutex`
- Git / GitHub

## Project Structure

```text
TCP-Client-Server/
├── include/
│   ├── Client.hpp
│   └── Server.hpp
├── src/
│   ├── Client.cpp
│   └── Server.cpp
├── examples/
│   ├── client_main.cpp
│   └── main.cpp
├── CMakeLists.txt
└── README.md

## How It Works

The server listens for incoming TCP connections on port 8080.

Each connected client is handled by a separate thread. Messages received from a client are broadcast to the other connected clients.

The client uses a separate thread to receive messages, allowing it to send and receive messages simultaneously.

Example
Client 1:
You: Hello everyone!


Client 2:
Server: Hello everyone!


Client 2:
You: Hello!


Client 1:
Server: Hello!

## Building Requirements
C++ compiler
CMake
Windows with Winsock2 or a Unix-like system with POSIX sockets
Build

From the project directory:

mkdir build
cd build
cmake ..
cmake --build . --config Release

## Running

Start the server:

.\Release\TCPServerExample.exe

Then open another terminal and start a client:

.\Release\TCPClientExample.exe

Multiple clients can be started in separate terminals.

## Disconnecting

To close the client connection, type:

/exit

The client closes its connection and the server removes it from the list of active clients.

## What I Learned

This project helped me practice:

TCP socket programming
Client-server architecture
Multithreading in C++
Thread synchronization with mutexes
Network communication
Socket and resource management
CMake project configuration
Cross-platform programming concepts
Debugging and handling compilation and runtime errors
Future Improvements

## Possible future improvements include:

Usernames for connected clients
Private messages
Improved message protocol
Better connection and error handling
Graceful server shutdown
Message timestamps
Logging
Automated tests
Author

Małgorzata Wójcik