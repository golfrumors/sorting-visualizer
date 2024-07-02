#include "visualizer.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>

Visualizer::Visualizer(int width, int height, int size) 
    : window(sf::VideoMode(width, height), "Sorting Algorithm Visualizer"), 
      arraySize(size), 
      currentAlgorithm(SortingAlgorithm::BubbleSort),
      isDropdownOpen(false),
      isSorting(false),
      sortingIndex(0),
      sortingSubIndex(0),
      quickSortLow(0),
      quickSortHigh(size - 1),
      quickSortPartitionIndex(0),
      isSortingComplete(false) {
    generateRandomArray();
    resetColors();
    createDropdown();
}

void Visualizer::createDropdown() {
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    algorithmNames = {"Bubble Sort", "Quick Sort", "Selection Sort"};

    dropdownBox.setSize(sf::Vector2f(200, 30));
    dropdownBox.setFillColor(sf::Color::White);
    dropdownBox.setOutlineThickness(2);
    dropdownBox.setOutlineColor(sf::Color::Black);
    dropdownBox.setPosition(10, 10);

    dropdownText.setFont(font);
    dropdownText.setString(algorithmNames[0]);
    dropdownText.setCharacterSize(20);
    dropdownText.setFillColor(sf::Color::Black);
    dropdownText.setPosition(15, 15);

    for (size_t i = 0; i < algorithmNames.size(); ++i) {
        sf::Text item;
        item.setFont(font);
        item.setString(algorithmNames[i]);
        item.setCharacterSize(20);
        item.setFillColor(sf::Color::Black);
        item.setPosition(15, 45 + i * 30);
        dropdownItems.push_back(item);
    }
}

void Visualizer::handleDropdown() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

    if (dropdownBox.getGlobalBounds().contains(worldPos)) {
        isDropdownOpen = !isDropdownOpen;
    } else if (isDropdownOpen) {
        for (size_t i = 0; i < algorithmNames.size(); ++i) {
            sf::FloatRect itemBounds(10, 40 + i * 30, 200, 30);
            if (itemBounds.contains(worldPos)) {
                dropdownText.setString(algorithmNames[i]);
                currentAlgorithm = static_cast<SortingAlgorithm>(i);
                isDropdownOpen = false;
                break;
            }
        }
    }
}

void Visualizer::drawDropdown() {
    window.draw(dropdownBox);
    window.draw(dropdownText);

    if (isDropdownOpen) {
        sf::RectangleShape dropdownList(sf::Vector2f(200, 30 * algorithmNames.size()));
        dropdownList.setFillColor(sf::Color::White);
        dropdownList.setOutlineThickness(2);
        dropdownList.setOutlineColor(sf::Color::Black);
        dropdownList.setPosition(10, 40);
        window.draw(dropdownList);

        for (size_t i = 0; i < algorithmNames.size(); ++i) {
            sf::Text item = dropdownItems[i];
            item.setPosition(15, 45 + i * 30);
            window.draw(item);
        }
    }
}

void Visualizer::drawBars() {
    float barWidth = static_cast<float>(window.getSize().x) / arraySize;
    for (int i = 0; i < arraySize; ++i) {
        sf::RectangleShape bar(sf::Vector2f(barWidth - 1, array[i] * 2));
        bar.setPosition(i * barWidth, window.getSize().y - array[i] * 2);
        bar.setFillColor(isSortingComplete ? sf::Color::Green : barColors[i]);
        window.draw(bar);
    }
}

void Visualizer::generateRandomArray() {
    array.resize(arraySize);
    for (int i = 0; i < arraySize; ++i) {
        array[i] = rand() % (window.getSize().y / 2) + 1;
    }
    resetColors();
}

void Visualizer::resetColors() {
    barColors.clear();
    barColors.resize(arraySize, sf::Color::White);
    isSortingComplete = false;
}

void Visualizer::sortStep() {
    switch (currentAlgorithm) {
        case SortingAlgorithm::BubbleSort:
            bubbleSortStep();
            break;
        case SortingAlgorithm::QuickSort:
            quickSortStep();
            break;
        case SortingAlgorithm::SelectionSort:
            selectionSortStep();
            break;
    }
}

void Visualizer::bubbleSortStep() {
    if (sortingIndex < arraySize - 1) {
        if (sortingSubIndex < arraySize - sortingIndex - 1) {
            barColors[sortingSubIndex] = sf::Color::Red;
            barColors[sortingSubIndex + 1] = sf::Color::Red;

            if (array[sortingSubIndex] > array[sortingSubIndex + 1]) {
                std::swap(array[sortingSubIndex], array[sortingSubIndex + 1]);
            }

            sortingSubIndex++;
        } else {
            barColors[arraySize - sortingIndex - 1] = sf::Color::Green;
            sortingIndex++;
            sortingSubIndex = 0;
        }
    } else {
        isSorting = false;
        isSortingComplete = true;
    }
}

void Visualizer::quickSortStep() {
    if (quickSortLow < quickSortHigh) {
        if (quickSortPartitionIndex == 0) {
            quickSortPartitionIndex = quickSortPartition(quickSortLow, quickSortHigh);
        } else {
            int newHigh = quickSortPartitionIndex - 1;
            quickSortStack.push(std::make_pair(quickSortPartitionIndex + 1, quickSortHigh));
            quickSortHigh = newHigh;
            quickSortPartitionIndex = 0;
        }
    } else if (!quickSortStack.empty()) {
        std::tie(quickSortLow, quickSortHigh) = quickSortStack.top();
        quickSortStack.pop();
        quickSortPartitionIndex = 0;
    } else {
        isSorting = false;
        isSortingComplete = true;
    }
}

int Visualizer::quickSortPartition(int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        barColors[j] = sf::Color::Red;
        barColors[high] = sf::Color::Blue;

        if (array[j] < pivot) {
            i++;
            std::swap(array[i], array[j]);
            barColors[i] = sf::Color::Yellow;
        }
    }

    std::swap(array[i + 1], array[high]);
    barColors[i + 1] = sf::Color::Green;

    return i + 1;
}

void Visualizer::selectionSortStep() {
    if (sortingIndex < arraySize - 1) {
        int minIdx = sortingIndex;
        barColors[sortingIndex] = sf::Color::Red;

        for (int i = sortingIndex + 1; i < arraySize; i++) {
            barColors[i] = sf::Color::Yellow;
            if (array[i] < array[minIdx]) {
                barColors[minIdx] = sf::Color::White;
                minIdx = i;
                barColors[minIdx] = sf::Color::Red;
            }
        }

        if (minIdx != sortingIndex) {
            std::swap(array[sortingIndex], array[minIdx]);
        }

        barColors[sortingIndex] = sf::Color::Green;
        sortingIndex++;
    } else {
        isSorting = false;
        isSortingComplete = true;
    }
}

void Visualizer::run() {
    sf::Clock clock;
    const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                handleDropdown();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    if(!isSortingComplete) {
                        isSorting = !isSorting;
                        if (isSorting) {
                            sortingIndex = 0;
                            sortingSubIndex = 0;
                            quickSortLow = 0;
                            quickSortHigh = arraySize - 1;
                            quickSortPartitionIndex = 0;
                            while (!quickSortStack.empty()) quickSortStack.pop();
                        }
                    }
                } else if (event.key.code == sf::Keyboard::R) {
                    generateRandomArray();
                    isSorting = false;
                    isSortingComplete = false;
                    resetColors();
                }
            }
        }
        
        if (isSorting) {
            sortStep();
        }

        window.clear(sf::Color::Black);
        drawBars();
        drawDropdown();
        window.display();

        sf::sleep(timePerFrame - elapsed);
    }
}
