#include "LoggingLibrary.h"

int main() {
    std::string client = "Internet Heroes";
  
    // Встановлення налаштувань виводу
    LoggingLibrary::setLogOutput(LoggingLibrary::CONSOLE);  // Змінити на LoggingLibrary::CONSOLE або LoggingLibrary::FILE при необхідності

    // Логування повідомлення
    LoggingLibrary::logMessage("This is an info message", LoggingLibrary::INFO_LOG, client);
    LoggingLibrary::logMessage("This is a warning message", LoggingLibrary::WARNING_LOG, client);
    LoggingLibrary::logMessage("This is an error message", LoggingLibrary::ERROR_LOG, client);

    return 0;
}
