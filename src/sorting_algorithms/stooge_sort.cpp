#include "stooge_sort.h"
#include <algorithm>

void StoogeSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (isSortingComplete) {
        for (int i = 0; i < array.size(); ++i) {
            colors[i] = sf::Color::Green;
        }
        return;
    }

    if (stack.empty()) {
        stack.push_back({0, (int)array.size() - 1});
    }

    stoogeSortStep(array, colors, audioManager);

    if (isSortingComplete) {
        for (int i = 0; i < array.size(); ++i) {
            colors[i] = sf::Color::Green;
        }
    }
}

void StoogeSort::stoogeSortStep(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (stack.empty()) {
        isSortingComplete = true;
        return;
    }

    auto [l, h] = stack.back();
    stack.pop_back();

    if (array[l] > array[h]) {
        std::swap(array[l], array[h]);
        incrementArrayAccesses(4);
        incrementComparisons();
        colors[l] = sf::Color::Red;
        colors[h] = sf::Color::Red;
        playSound(array[l], array.size(), audioManager);
        playSound(array[h], array.size(), audioManager);
    }

    for (int k = 0; k < array.size(); ++k) {
        if (colors[k] != sf::Color::Red) {
            colors[k] = sf::Color::White;
        }
    }

    if (h - l + 1 > 2) {
        int t = (h - l + 1) / 3;
        stack.push_back({l, h - t});
        stack.push_back({l + t, h});
        stack.push_back({l, h - t});
    }
}

void StoogeSort::reset() {
    isSortingComplete = false;
    l = 0;
    h = 0;
    stage = 0;
    stack.clear();
    comparisons = 0;
    arrayAccesses = 0;
}

bool StoogeSort::isFinished() const {
    return isSortingComplete;
}
