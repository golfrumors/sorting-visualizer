#include "bogo_sort.h"
#include <algorithm>
#include <random>

void BogoSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (isSortingComplete) {
        for (int i = 0; i < array.size(); ++i) {
            colors[i] = sf::Color::Green;
        }
        return;
    }

    if (isSorted(array)) {
        isSortingComplete = true;
        for (int i = 0; i < array.size(); ++i) {
            colors[i] = sf::Color::Green;
        }
    } else {
        shuffle(array, colors, audioManager);
    }
}

bool BogoSort::isSorted(const std::vector<int>& array) {
    for (int i = 1; i < array.size(); ++i) {
        incrementComparisons();
        if (array[i - 1] > array[i]) {
            return false;
        }
    }
    return true;
}

void BogoSort::shuffle(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    static std::random_device rd;
    static std::mt19937 g(rd());

    std::shuffle(array.begin(), array.end(), g);

    for (int i = 0; i < array.size(); ++i) {
        colors[i] = sf::Color::Red;
        playSound(array[i], array.size(), audioManager);
        incrementArrayAccesses(1);
    }
}

void BogoSort::reset() {
    isSortingComplete = false;
    comparisons = 0;
    arrayAccesses = 0;
}

bool BogoSort::isFinished() const {
    return isSortingComplete;
}

