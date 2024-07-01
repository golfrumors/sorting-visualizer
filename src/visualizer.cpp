#include "visualizer.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>

Visualizer::Visualizer(int width, int height, int size) 
    : window(sf::VideoMode(width, height), "Sorting Algorithm Visualizer"), arraySize(size) {
    generateRandomArray();
    resetColors();
}

void Visualizer::resetColors() {
    barColors.resize(arraySize, sf::Color::White);
}

void Visualizer::setColor(int index, sf::Color color) {
    barColors[index] = color;
}

void Visualizer::generateRandomArray() {
    array.resize(arraySize);
    for (int i = 0; i < arraySize; ++i) {
        array[i] = i + 1;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(array.begin(), array.end(), g);
    resetColors();
}

void Visualizer::draw() {
    window.clear(sf::Color::Black);
    float barWidth = static_cast<float>(window.getSize().x) / arraySize;
    for (int i = 0; i < arraySize; ++i) {
        sf::RectangleShape bar(sf::Vector2f(barWidth, array[i] * 2));
        bar.setPosition(i * barWidth, window.getSize().y - array[i] * 2);
        bar.setFillColor(barColors[i]);
        window.draw(bar);
    }
    window.display();
}

void Visualizer::bubbleSort() {
    for (int i = 0; i < arraySize - 1; ++i) {
        for (int j = 0; j < arraySize - i - 1; ++j) {
            setColor(j, sf::Color::Red);
            setColor(j + 1, sf::Color::Red);
            draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                draw();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            setColor(j, sf::Color::White);
            setColor(j + 1, sf::Color::White);
        }
        setColor(arraySize - i - 1, sf::Color::Green);
    }
    resetColors();
}

void Visualizer::quickSort() {
    quickSortHelper(0, arraySize - 1);
}

void Visualizer::quickSortHelper(int low, int high) {
    if(low < high) {
        int pi = partition(low, high);
        quickSortHelper(low, pi - 1);
        quickSortHelper(pi + 1, high);
    }
}

int Visualizer::partition(int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for(int j = low; j <= high - 1; j++) {
        if(array[j] < pivot) {
            i++;
            std::swap(array[i], array[j]);
            draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    std::swap(array[i + 1], array[high]);
    draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return (i + 1);
}

void Visualizer::selectionSort() {
    for(int i = 0; i < arraySize - 1; i++) {
        int minIdx = i;
        for(int j = i + 1; j < arraySize; j++) {
            if(array[j] < array[minIdx]) minIdx = j;
        }

        if(minIdx != i) {
            std::swap(array[i], array[minIdx]);
            draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

void Visualizer::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    switch(currentAlgorithm)
                    {
                        case SortingAlgorithm::BubbleSort:
                            bubbleSort();
                            break;
                        case SortingAlgorithm::QuickSort:
                            quickSort();
                            break;
                        case SortingAlgorithm::SelectionSort:
                            selectionSort();
                            break;
                    }
                } else if (event.key.code == sf::Keyboard::R) {
                    generateRandomArray();
                } else if (event.key.code == sf::Keyboard::B) {
                    currentAlgorithm = SortingAlgorithm::BubbleSort;
                } else if (event.key.code == sf::Keyboard::Q) {
                    currentAlgorithm = SortingAlgorithm::QuickSort;
                } else if (event.key.code == sf::Keyboard::S) {
                    currentAlgorithm = SortingAlgorithm::SelectionSort;
                }
            }
        }
        draw();
    }
}
