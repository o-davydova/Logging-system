cmake_minimum_required(VERSION 3.10)
project(ClientApp)

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601) # Windows 7
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(ClientApp ClientApp.cpp)
target_link_libraries(ClientApp logging)

if(WIN32)
    target_link_libraries(ClientApp ws2_32)
endif()
