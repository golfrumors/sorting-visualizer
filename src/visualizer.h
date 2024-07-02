#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <stack>

class Visualizer {
public:
    Visualizer(int width, int height, int arraySize);
    void run();

private:
    void createDropdown();
    void handleDropdown();
    void drawDropdown();
    void drawBars();
    void generateRandomArray();
    void resetColors();
    void sortStep();

    void bubbleSortStep();
    void quickSortStep();
    void selectionSortStep();
    int quickSortPartition(int low, int high);

    enum class SortingAlgorithm {
        BubbleSort,
        QuickSort,
        SelectionSort
    };

    sf::RenderWindow window;
    std::vector<int> array;
    std::vector<sf::Color> barColors;
    int arraySize;
    SortingAlgorithm currentAlgorithm;

    sf::Font font;
    sf::Text dropdownText;
    sf::RectangleShape dropdownBox;
    std::vector<std::string> algorithmNames;
    bool isDropdownOpen;
    std::vector<sf::Text> dropdownItems;

    bool isSorting;
    bool isSortingComplete;
    int sortingIndex;
    int sortingSubIndex;

    int quickSortLow;
    int quickSortHigh;
    int quickSortPartitionIndex;
    std::stack<std::pair<int, int>> quickSortStack;
};
