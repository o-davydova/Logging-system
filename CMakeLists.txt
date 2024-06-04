cmake_minimum_required(VERSION 3.10)

# Project name
project(LoggingProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories
add_subdirectory(LoggingServer)
add_subdirectory(LoggingLibrary)
add_subdirectory(ClientApp)
