cmake_minimum_required(VERSION 3.15)
project(fft)


set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(fft main.cpp fft.cpp)
target_link_directories(fft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(fft ${OpenCV_LIBS})

