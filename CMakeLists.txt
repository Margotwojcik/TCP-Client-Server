cmake_minimum_required(VERSION 3.20)

project(TCPClientServer
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(TCPServer
    src/Server.cpp
)

target_include_directories(TCPServer
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(TCPServerExample
    examples/main.cpp
)

target_link_libraries(TCPServerExample
    PRIVATE
        TCPServer
)







if(WIN32)
    target_link_libraries(TCPServer
        PRIVATE
            ws2_32
    )
endif()

add_library(TCPClient
    src/Client.cpp
)

target_include_directories(TCPClient
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(TCPClientExample
    examples/client_main.cpp
)



target_link_libraries(TCPClientExample
    PRIVATE
        TCPClient
)

if(WIN32)
    target_link_libraries(TCPClient
        PRIVATE
            ws2_32
    )
endif()