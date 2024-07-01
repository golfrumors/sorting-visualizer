#include "visualizer.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>

Visualizer::Visualizer(int width, int height, int size) 
    : window(sf::VideoMode(width, height), "Sorting Algorithm Visualizer"), arraySize(size) {
    generateRandomArray();
}

void Visualizer::generateRandomArray() {
    array.resize(arraySize);
    for (int i = 0; i < arraySize; ++i) {
        array[i] = i + 1;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(array.begin(), array.end(), g);
}

void Visualizer::draw() {
    window.clear(sf::Color::Black);
    float barWidth = static_cast<float>(window.getSize().x) / arraySize;
    for (int i = 0; i < arraySize; ++i) {
        sf::RectangleShape bar(sf::Vector2f(barWidth, array[i] * 2));
        bar.setPosition(i * barWidth, window.getSize().y - array[i] * 2);
        bar.setFillColor(sf::Color::White);
        window.draw(bar);
    }
    window.display();
}

void Visualizer::bubbleSort() {
    for (int i = 0; i < arraySize - 1; ++i) {
        for (int j = 0; j < arraySize - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
                draw();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
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
                    bubbleSort();
                } else if (event.key.code == sf::Keyboard::R) {
                    generateRandomArray();
                }
            }
        }
        draw();
    }
}
