#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <stack>
#include <memory>
#include "sorting_algorithm.h"
#include "audio_manager.h"

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

    enum class SortingAlgorithmType {
        BubbleSort,
        QuickSort,
        SelectionSort,
        InsertionSort,
        MergeSort,
        HeapSort,
        CountingSort
    };

    sf::RenderWindow window;
    std::vector<int> array;
    std::vector<sf::Color> barColors;
    int arraySize;
    SortingAlgorithmType currentAlgorithmType;
    std::unique_ptr<SortingAlgorithm> currentAlgorithm;

    sf::Font font;
    sf::Text dropdownText;
    sf::RectangleShape dropdownBox;
    std::vector<std::string> algorithmNames;
    bool isDropdownOpen;
    std::vector<sf::Text> dropdownItems;

    bool isSorting;
    bool isSortingComplete;

    AudioManager audioManager;

    void initializeSortingAlgorithm();
    void drawStats();
};