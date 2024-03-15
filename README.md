# Logging System
## Overview
This logging system is designed to facilitate the transmission of messages from user applications to a centralized logging server. It consists of a client library and a logging server, enabling the collection, processing, and outputting of logs to standard output.

## Features
* **Client Library:** Allows integration with user applications to send log messages to the logging server.
* **Logging Server:** Collects incoming log messages, processes them, and outputs them to standard output.

## Usage
### Client Library
To integrate the client library into your application, include the necessary header files from the include directory and link against the library when building your application.

```cpp
#include <logging_client.h>

// Usage example
logging_client::log("This is a log message");
```

### Logging Server
The logging server can be run as a standalone application. It listens for incoming log messages from client applications and processes them accordingly.

```bash
./logging_server
```

## Installation
### Dependencies
* C++17 compiler
* CMake 3.10 or higher
### Build Instructions
```bash
mkdir build
cd build
cmake ..
make
```

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes.

