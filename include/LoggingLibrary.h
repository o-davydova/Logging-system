// LoggingLibrary.h
#ifndef LOGGINGLIBRARY_H
#define LOGGINGLIBRARY_H

#include <string>

class LoggingLibrary {
public:
    enum LogLevel {
        INFO_LOG = 1,
        WARNING_LOG = 2,
        ERROR_LOG = 3
    };

    enum LogOutput {
        CONSOLE = 1,
        FILE = 2,
        BOTH = 3
    };

    static void logMessage(const std::string& message, LogLevel level, const std::string& client_name = "unknown");
    static void setLogOutput(LogOutput output);

private:
    static LogOutput currentLogOutput;
};

#endif // LOGGINGLIBRARY_H
