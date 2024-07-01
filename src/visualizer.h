#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Visualizer {
public:
    Visualizer(int width, int height, int arraySize);
    void run();

private:
    void generateRandomArray();
    void draw();
    void bubbleSort();  // We'll start with bubble sort

    sf::RenderWindow window;
    std::vector<int> array;
    int arraySize;
};
