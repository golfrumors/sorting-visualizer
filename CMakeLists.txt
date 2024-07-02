cmake_minimum_required(VERSION 3.10)
project(SortingVisualizer)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(SortingVisualizer src/main.cpp src/visualizer.cpp)

target_link_libraries(SortingVisualizer sfml-graphics sfml-window sfml-system)

file(COPY ${CMAKE_SOURCE_DIR}/arial.ttf DESTINATION ${CMAKE_BINARY_DIR})