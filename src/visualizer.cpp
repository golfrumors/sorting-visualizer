#include "visualizer.h"
#include "sorting_algorithms/bubble_sort.h"
#include "sorting_algorithms/quick_sort.h"
#include "sorting_algorithms/selection_sort.h"
#include "sorting_algorithms/insertion_sort.h"
#include "sorting_algorithms/merge_sort.h"
#include "sorting_algorithms/heap_sort.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>

Visualizer::Visualizer(int width, int height, int size)
    : window(sf::VideoMode(width, height), "Sorting Algorithm Visualizer"),
      arraySize(size),
      currentAlgorithmType(SortingAlgorithmType::BubbleSort),
      isDropdownOpen(false),
      isSorting(false),
      isSortingComplete(false) {
    generateRandomArray();
    resetColors();
    createDropdown();
    initializeSortingAlgorithm();
}

void Visualizer::createDropdown() {
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    algorithmNames = {"Bubble Sort", "Quick Sort", "Selection Sort", "Insertion Sort", "Merge Sort", "Heap Sort"};

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
                currentAlgorithmType = static_cast<SortingAlgorithmType>(i);
                isDropdownOpen = false;
                initializeSortingAlgorithm();
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
    if (!currentAlgorithm->isFinished()) {
        currentAlgorithm->step(array, barColors, audioManager);
    } else {
        isSorting = false;
        isSortingComplete = true;
        audioManager.stopSound();
    }
}

void Visualizer::initializeSortingAlgorithm() {
    switch (currentAlgorithmType) {
        case SortingAlgorithmType::BubbleSort:
            currentAlgorithm = std::make_unique<BubbleSort>();
            break;
        case SortingAlgorithmType::QuickSort:
            currentAlgorithm = std::make_unique<QuickSort>();
            break;
        case SortingAlgorithmType::SelectionSort:
            currentAlgorithm = std::make_unique<SelectionSort>();
            break;
        case SortingAlgorithmType::InsertionSort:
            currentAlgorithm = std::make_unique<InsertionSort>();
            break;
        case SortingAlgorithmType::MergeSort:
            currentAlgorithm = std::make_unique<MergeSort>();
            break;
        case SortingAlgorithmType::HeapSort:
            currentAlgorithm = std::make_unique<HeapSort>();
            break;
    }
    currentAlgorithm->reset();
}

void Visualizer::drawStats() {
    std::string stats = "Comparisons: " + std::to_string(currentAlgorithm->getComparisons()) + 
                        "\nArray Accesses: " + std::to_string(currentAlgorithm->getArrayAccesses());
    sf::Text statsText;
    statsText.setFont(font);
    statsText.setString(stats);
    statsText.setCharacterSize(20);
    statsText.setFillColor(sf::Color::Red);
    statsText.setPosition(300, window.getSize().y - 600);
    window.draw(statsText);
}

void Visualizer::run() {
    sf::Clock clock;
    const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if(isSortingComplete)
                audioManager.stopSound();
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                handleDropdown();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    if(!isSortingComplete) {
                        isSorting = !isSorting;
                        audioManager.stopSound();
                        if (isSorting) {
                            currentAlgorithm->reset();
                        }
                    }
                } else if (event.key.code == sf::Keyboard::R) {
                    generateRandomArray();
                    isSorting = false;
                    isSortingComplete = false;
                    resetColors();
                    audioManager.stopSound();
                    currentAlgorithm->reset();
                }
            }
        }

        if (isSorting) {
            sortStep();
            //@TODO : Implement this delay for fast sorting algorithms, beause others become unfathomably slow otherwise
            //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        window.clear(sf::Color::Black);
        drawBars();
        drawDropdown();
        drawStats();
        window.display();

        // sf::sleep(timePerFrame - elapsed);
    }
}
