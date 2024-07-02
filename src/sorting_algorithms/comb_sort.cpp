#include "headers/comb_sort.h"
#include <cmath>
#include <algorithm>

void CombSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (gap == 0) {
        gap = array.size();
    }

    gap = std::max(1, static_cast<int>(gap / 1.3));
    swapped = false;

    for (i = 0; i + gap < array.size(); ++i) {
        if (array[i] > array[i + gap]) {
            std::swap(array[i], array[i + gap]);
            colors[i] = sf::Color::Red;
            colors[i + gap] = sf::Color::Green;
            playSound(array[i], array.size(), audioManager);
            incrementArrayAccesses(4);
            incrementComparisons();
            swapped = true;
        } else {
            colors[i] = sf::Color::White;
            colors[i + gap] = sf::Color::White;
            incrementComparisons();
        }
    }

    if (gap == 1 && !swapped) {
        isSortingComplete = true;
        for (int k = 0; k < array.size(); ++k) {
            colors[k] = sf::Color::Green;
        }
    }
}

void CombSort::reset() {
    isSortingComplete = false;
    gap = 0;
    i = 0;
    swapped = false;
    comparisons = 0;
    arrayAccesses = 0;
}

bool CombSort::isFinished() const {
    return isSortingComplete;
}

