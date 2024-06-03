cmake_minimum_required(VERSION 3.10)
project(LoggingServer)

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601) # Windows 7
endif()

add_executable(LoggingServer LoggingServer.cpp)

if(WIN32)
    target_link_libraries(LoggingServer ws2_32)
endif()
