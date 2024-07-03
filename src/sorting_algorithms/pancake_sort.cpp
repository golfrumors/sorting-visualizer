#include "pancake_sort.h"
#include <algorithm>

void PancakeSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (isSortingComplete) {
        for (int k = 0; k < array.size(); ++k) {
            colors[k] = sf::Color::Green;
        }
        return;
    }

    int n = array.size();
    if (i >= n) {
        isSortingComplete = true;
        for (int k = 0; k < array.size(); ++k) {
            colors[k] = sf::Color::Green;
        }
        return;
    }

    int maxIdx = findMax(array, n - i, colors);
    if (maxIdx != n - i - 1) {
        flip(array, maxIdx + 1, colors, audioManager);
        flip(array, n - i, colors, audioManager);
    }

    i++;
}

void PancakeSort::flip(std::vector<int>& array, int k, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    int start = 0;
    while (start < k - 1) {
        std::swap(array[start], array[k - 1]);
        incrementArrayAccesses(4);
        incrementComparisons();
        colors[start] = sf::Color::Red;
        colors[k - 1] = sf::Color::Red;
        playSound(array[start], array.size(), audioManager);
        start++;
        k--;
    }
}

int PancakeSort::findMax(std::vector<int>& array, int n, std::vector<sf::Color>& colors) {
    int maxIdx = 0;
    for (int j = 1; j < n; ++j) {
        if (array[j] > array[maxIdx]) {
            maxIdx = j;
        }
        incrementComparisons();
    }
    return maxIdx;
}

void PancakeSort::reset() {
    isSortingComplete = false;
    i = 0;
    comparisons = 0;
    arrayAccesses = 0;
}

bool PancakeSort::isFinished() const {
    return isSortingComplete;
}

