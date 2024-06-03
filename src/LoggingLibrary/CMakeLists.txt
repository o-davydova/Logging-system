cmake_minimum_required(VERSION 3.10)
project(LoggingLibrary)

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601) # Windows 7
endif()

add_library(logging STATIC LoggingLibrary.cpp)
target_include_directories(logging PUBLIC ${CMAKE_SOURCE_DIR}/include)

if(WIN32)
    target_link_libraries(logging ws2_32)
endif()
