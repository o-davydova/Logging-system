#include <LoggingLibrary.hpp>
#include <string>

int main() {
    std::string client = "Internet Heroes";
    // Uncomment and set the desired log output
    // LoggingLibrary::setLogOutput(LoggingLibrary::CONSOLE);  // or LoggingLibrary::FILE

    // Log messages with different levels
    LoggingLibrary::logMessage("System startup complete", LogLevel::INFO_LOG, client);
    LoggingLibrary::logMessage("User 'John Doe' logged in", LogLevel::INFO_LOG, client);
    LoggingLibrary::logMessage("Configuration file loaded successfully", LogLevel::INFO_LOG, client);
    LoggingLibrary::logMessage("Potential security risk detected", LogLevel::WARNING_LOG, client);
    LoggingLibrary::logMessage("Disk space running low on drive C:", LogLevel::WARNING_LOG, client);
    LoggingLibrary::logMessage("High memory usage detected", LogLevel::WARNING_LOG, client);
    LoggingLibrary::logMessage("Failed to connect to database", LogLevel::ERROR_LOG, client);
    LoggingLibrary::logMessage("Critical error: application crashed", LogLevel::ERROR_LOG, client);
    LoggingLibrary::logMessage("Unauthorized access attempt detected", LogLevel::ERROR_LOG, client);
    LoggingLibrary::logMessage("Background process completed successfully", LogLevel::INFO_LOG, client);
    LoggingLibrary::logMessage("Network latency detected", LogLevel::WARNING_LOG, client);
    LoggingLibrary::logMessage("File not found: /path/to/file.txt", LogLevel::ERROR_LOG, client);
    LoggingLibrary::logMessage("Update available for application", LogLevel::INFO_LOG, client);
    LoggingLibrary::logMessage("Temporary file deleted", LogLevel::INFO_LOG, client);
    LoggingLibrary::logMessage("New user 'Alice' created", LogLevel::INFO_LOG, client);
    LoggingLibrary::logMessage("Unexpected input detected", LogLevel::WARNING_LOG, client);
    LoggingLibrary::logMessage("Permission denied for resource access", LogLevel::ERROR_LOG, client);
    LoggingLibrary::logMessage("Backup completed successfully", LogLevel::INFO_LOG, client);


    return 0;
}
