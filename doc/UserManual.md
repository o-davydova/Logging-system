
# User Guide for Logging System

## Overview

This guide provides instructions on how to use the Logging System, which includes a client application and a logging server. The system allows for logging messages of different levels (INFO, WARNING, ERROR) and supports output to both console and file.

## Components

The Logging System consists of the following files:

- `ClientApp.cpp`: The client application that logs messages.
- `LoggingLibrary.cpp`: The implementation of the logging functionality.
- `LoggingLibrary.h`: The header file for the logging library.
- `LoggingServer.cpp`: The server application that receives and processes log messages.

## Client Application

The client application (`ClientApp.cpp`) uses the logging library to send log messages to the logging server. Follow the steps below to compile and run the client application.

### Compilation

To compile the client application, use the following command (assuming you have `g++` installed):

```sh
g++ ClientApp.cpp LoggingLibrary.cpp -o ClientApp
```

### Running the Client Application

To run the client application, use the following command:

```sh
./ClientApp
```

### Configuration

In `ClientApp.cpp`, you can configure the output settings by uncommenting the appropriate line:

```cpp
// LoggingLibrary::setLogOutput(LoggingLibrary::CONSOLE);  // Change to LoggingLibrary::CONSOLE or LoggingLibrary::FILE as needed
```

- `LoggingLibrary::CONSOLE`: Logs messages to the console.
- `LoggingLibrary::FILE`: Logs messages to a file.
- `LoggingLibrary::BOTH`: Logs messages to both console and file (default setting).

### Logging Messages

The `ClientApp.cpp` logs messages of different levels as shown below:

```cpp
LoggingLibrary::logMessage("This is an info message", LoggingLibrary::INFO_LOG, client);
LoggingLibrary::logMessage("This is a warning message", LoggingLibrary::WARNING_LOG, client);
LoggingLibrary::logMessage("This is an error message", LoggingLibrary::ERROR_LOG, client);
```

## Logging Library

The logging library (`LoggingLibrary.cpp` and `LoggingLibrary.h`) provides the following functionalities:

- Logging messages with different levels (INFO, WARNING, ERROR).
- Configuring the log output (console, file, or both).

### Methods

#### `logMessage`

Logs a message with the specified level and client name.

```cpp
static void logMessage(const std::string& message, LogLevel level, const std::string& client_name = "unknown");
```

#### `setLogOutput`

Sets the log output configuration.

```cpp
static void setLogOutput(LogOutput output);
```

## Logging Server

The logging server (`LoggingServer.cpp`) receives log messages from the client application and outputs them based on the specified settings.

### Compilation

To compile the logging server, use the following command (assuming you have `g++` installed):

```sh
g++ LoggingServer.cpp -o LoggingServer
```

### Running the Logging Server

To run the logging server, use the following command:

```sh
./LoggingServer
```

### Functionality

The logging server listens on port 8080 for incoming log messages. It outputs the log messages to the console, a file (`server_logs.txt`), or both, based on the settings received from the client.

## Example Usage

1. Compile and run the logging server:

    ```sh
    g++ LoggingServer.cpp -o LoggingServer
    ./LoggingServer
    ```

2. Compile and run the client application:

    ```sh
    g++ ClientApp.cpp LoggingLibrary.cpp -o ClientApp
    ./ClientApp
    ```

3. Check the console output and the `server_logs.txt` file for logged messages.

## Conclusion

This guide covers the basic usage of the Logging System. You can customize the client application and logging server according to your requirements by modifying the provided source files. For any issues or further customization, please refer to the source code comments and documentation
