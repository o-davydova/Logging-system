#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#ifdef _WIN32
#include <ws2tcpip.h>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

constexpr int port = 8080;
constexpr const char* log_file = "server_logs.txt";


void logMessage(const std::string& message, bool writeToConsole, bool writeToFile) {
    if (writeToFile) {
        std::ofstream logFile(log_file, std::ios_base::app);
        if (!logFile.is_open()) {
            std::cerr << "Unable to open log file" << std::endl;
            return;
        }

        // Log to file
        logFile << message << std::endl;
        logFile.close();
    }

    if (writeToConsole) {
        // Log to console
        std::cout << message << std::endl;
    }
}

int main() {
#ifdef _WIN32
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cerr << "WSAStartup failed with error: " << iResult << std::endl;
        return 1;
    }
#endif

    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
#ifdef _WIN32
        std::cerr << "Socket failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
#else
        perror("socket failed");
#endif
        exit(EXIT_FAILURE);
    }

#ifdef _WIN32
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0) {
        std::cerr << "setsockopt failed with error: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
#elif defined(__APPLE__) || defined(__MACH__)
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
#else
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEport, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
#endif

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
#ifdef _WIN32
        std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
#else
        perror("bind failed");
        close(server_fd);
#endif
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
#ifdef _WIN32
        std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
#else
        perror("listen");
#endif
        exit(EXIT_FAILURE);
    }

    std::cout << "Logging server is listening on port " << port << std::endl;

    while (true) {
        int new_socket;
        struct sockaddr_in client_address;
        socklen_t client_addrlen = sizeof(client_address);
        if ((new_socket = accept(server_fd, (struct sockaddr*)&client_address, &client_addrlen)) < 0) {
#ifdef _WIN32
            std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
#else
            perror("accept");
#endif
            exit(EXIT_FAILURE);
        }

        int valread = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
        if (valread > 0) {
            buffer[valread] = '\0';  // Ensure null termination
            std::string message(buffer);

            // Receive output settings from the client
            bool writeToConsole, writeToFile;
            recv(new_socket, reinterpret_cast<char*>(&writeToConsole), sizeof(bool), 0);
            recv(new_socket, reinterpret_cast<char*>(&writeToFile), sizeof(bool), 0);

            logMessage(message, writeToConsole, writeToFile);
        }

#ifdef _WIN32
        closesocket(new_socket);
#else
        close(new_socket);
#endif
    }

#ifdef _WIN32
    closesocket(server_fd);
    WSACleanup();
#else
    close(server_fd);
#endif

    return 0;
}
