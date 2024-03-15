cmake_minimum_required(VERSION 3.15)
project(logging_system)

# Установка стандарту C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Створення бібліотеки для клієнтської частини системи логування
add_library(logging_client 
    src/logging_client.cpp
)

# Додавання директив для знаходження заголовочних файлів у папці include
target_include_directories(logging_client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Створення серверної частини системи логування
add_executable(logging_server 
    src/logging_server.cpp
)

# Додавання директив для знаходження заголовочних файлів у папці include
target_include_directories(logging_server PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Лінкування бібліотеки клієнтської частини з серверною частиною
target_link_libraries(logging_server PRIVATE logging_client)