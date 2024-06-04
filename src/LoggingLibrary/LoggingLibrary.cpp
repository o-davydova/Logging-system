#include <chrono>
#include <iomanip>
#include <iostream>
#include <LoggingLibrary.hpp>
#include <sstream>
#ifdef _WIN32
#include <ws2tcpip.h>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <unistd.h>
#endif

constexpr int port = 8080;

// Initialize static member
LogOutput LoggingLibrary::currentLogOutput = LogOutput::BOTH;

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
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return;
    }

    // get time std::chrono
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);

    // format time std::put_time
    std::tm local_time = *std::localtime(&time);
    std::ostringstream time_stream;
    time_stream << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");
    std::string dt = time_stream.str(); 


    // Form the log message
    std::string log_level;
    switch (level) {
    case LogLevel::INFO_LOG:
        log_level = "[INFO]";
        break;
    case LogLevel::WARNING_LOG:
        log_level = "[WARNING]";
        break;
    case LogLevel::ERROR_LOG:
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

    bool writeToFile = (currentLogOutput == LogOutput::FILE || currentLogOutput == LogOutput::BOTH);
    bool writeToConsole = (currentLogOutput == LogOutput::CONSOLE || currentLogOutput == LogOutput::BOTH);

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
