// LoggingLibrary.cpp
#include "LoggingLibrary.h"
#include <iostream>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <sstream>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <unistd.h>
#endif

#define PORT 8080

// Initialize static member
LoggingLibrary::LogOutput LoggingLibrary::currentLogOutput = LoggingLibrary::BOTH;

void LoggingLibrary::logMessage(const std::string& message, LogLevel level, const std::string& client_name) {
    int sock = 0;
    struct sockaddr_in serv_addr;

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return;
    }
#endif

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return;
    }

    // Get current time
    time_t now = time(0);
    char* dt = ctime(&now);
    dt[strlen(dt) - 1] = '\0';  // Remove newline character

    // Form the log message
    std::string log_level;
    switch (level) {
    case INFO_LOG:
        log_level = "[INFO]";
        break;
    case WARNING_LOG:
        log_level = "[WARNING]";
        break;
    case ERROR_LOG:
        log_level = "[ERROR]";
        break;
    default:
        log_level = "[UNKNOWN]";
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
        return;
    }

    std::ostringstream formatted_message;
    formatted_message << std::left << std::setw(10) << log_level
        << std::setw(25) << dt
        << std::setw(20) << client_name
        << message;
    std::string str_message = formatted_message.str();

    bool writeToFile = true;
    bool writeToConsole = true;

    if (currentLogOutput == FILE)
    {
        writeToFile = true;
        writeToConsole = false;
    }
    else if (currentLogOutput == CONSOLE)
    {
        writeToFile = false;
        writeToConsole = true;
    }
    // Send log message along with output settings
    send(sock, str_message.c_str(), str_message.size(), 0);
    send(sock, reinterpret_cast<const char*>(&writeToConsole), sizeof(bool), 0);
    send(sock, reinterpret_cast<const char*>(&writeToFile), sizeof(bool), 0);



#ifdef _WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif
}

void LoggingLibrary::setLogOutput(LogOutput output) {
    currentLogOutput = output;
}
