cmake_minimum_required(VERSION 3.10)
project(SortingVisualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src/headers)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Create executable
set(SOURCES
    src/main.cpp
    src/visualizer.cpp
    src/sorting_algorithms/sorting_algorithm.cpp
    src/sorting_algorithms/bubble_sort.cpp
    src/sorting_algorithms/quick_sort.cpp
    src/sorting_algorithms/selection_sort.cpp
    src/sorting_algorithms/insertion_sort.cpp
    src/sorting_algorithms/merge_sort.cpp
    src/sorting_algorithms/heap_sort.cpp
    src/sorting_algorithms/counting_sort.cpp
    src/sorting_algorithms/radix_sort.cpp
    src/sorting_algorithms/bucket_sort.cpp
    src/sorting_algorithms/shell_sort.cpp
    src/sorting_algorithms/tim_sort.cpp
    src/sorting_algorithms/comb_sort.cpp
    src/sorting_algorithms/pigeonhole_sort.cpp
    src/sorting_algorithms/cycle_sort.cpp
    src/sorting_algorithms/cocktail_sort.cpp
    src/sorting_algorithms/strand_sort.cpp
    src/sorting_algorithms/bitonic_sort.cpp
    src/audio/audio_manager.cpp
    src/audio/oscillator.cpp
)

set(HEADERS
    src/headers/visualizer.h
    src/headers/sorting_algorithm.h
    src/headers/bubble_sort.h
    src/headers/quick_sort.h
    src/headers/selection_sort.h
    src/headers/insertion_sort.h
    src/headers/merge_sort.h
    src/headers/heap_sort.h
    src/headers/counting_sort.h
    src/headers/radix_sort.h
    src/headers/bucket_sort.h
    src/headers/shell_sort.h
    src/headers/tim_sort.h
    src/headers/comb_sort.h
    src/headers/pigeonhole_sort.h
    src/headers/cycle_sort.h
    src/headers/cocktail_sort.h
    src/headers/strand_sort.h
    src/headers/bitonic_sort.h
    src/headers/audio_manager.h
    src/headers/oscillator.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
