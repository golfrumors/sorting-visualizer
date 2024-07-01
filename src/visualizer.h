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
    void bubbleSort();
    void quickSort();
    void quickSortHelper(int low, int high);
    void selectionSort();
    int partition(int low, int high);
    void resetColors();
    void setColor(int index, sf::Color color);

    sf::RenderWindow window;
    std::vector<int> array;
    std::vector<sf::Color> barColors;
    int arraySize;

    enum class SortingAlgorithm
    {
        BubbleSort,
        QuickSort,
        SelectionSort
    };

    SortingAlgorithm currentAlgorithm = SortingAlgorithm::BubbleSort;
};
