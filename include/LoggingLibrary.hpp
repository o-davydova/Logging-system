#ifndef LOGGINGLIBRARY_HPP
#define LOGGINGLIBRARY_HPP

#include <string>

enum class LogLevel {
    INFO_LOG,
    WARNING_LOG,
    ERROR_LOG
};

enum class LogOutput {
    CONSOLE,
    FILE,
    BOTH
};


class LoggingLibrary {
public:

    static void logMessage(const std::string& message, LogLevel level, const std::string& client_name = "unknown");
    static void setLogOutput(LogOutput output);

private:
    static LogOutput currentLogOutput;
};

#endif // LOGGINGLIBRARY_H
