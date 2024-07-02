cmake_minimum_required(VERSION 3.10)
project(SortingVisualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)

# Source files
set(SOURCES
    src/main.cpp
    src/visualizer.cpp
    src/sorting_algorithms/sorting_algorithm.cpp
    src/sorting_algorithms/bubble_sort.cpp
    src/sorting_algorithms/quick_sort.cpp
    src/sorting_algorithms/selection_sort.cpp
    src/audio/audio_manager.cpp
    src/audio/oscillator.cpp
)

# Header files
set(HEADERS
    src/visualizer.h
    src/sorting_algorithms/sorting_algorithm.h
    src/sorting_algorithms/bubble_sort.h
    src/sorting_algorithms/quick_sort.h
    src/sorting_algorithms/selection_sort.h
    src/audio/audio_manager.h
    src/audio/oscillator.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)

# Copy resources to build directory
# file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
