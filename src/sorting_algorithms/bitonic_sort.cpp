#include "headers/bitonic_sort.h"
#include <algorithm>

void BitonicSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (isSortingComplete) {
        for (int i = 0; i < array.size(); ++i) {
            colors[i] = sf::Color::Green;
        }
        return;
    }

    int n = array.size();
    if (size == 1) {
        size = 2;
    }

    if (size > n) {
        isSortingComplete = true;
        for (int i = 0; i < n; ++i) {
            colors[i] = sf::Color::Green;
        }
        return;
    }

    if (stepIndex < size / 2) {
        for (int i = stepIndex; i < n - size / 2; i += size) {
            compareAndSwap(array, i, i + size / 2, direction, colors, audioManager);
        }
        stepIndex++;
    } else {
        stepIndex = 0;
        size *= 2;
        direction = !direction;
    }

    // Update the array colors and sounds for visualization
    for (int i = 0; i < n; ++i) {
        colors[i] = sf::Color::White;
        playSound(array[i], array.size(), audioManager);
        incrementArrayAccesses(1);
    }
}

void BitonicSort::compareAndSwap(std::vector<int>& array, int i, int j, bool dir, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if ((dir && array[i] > array[j]) || (!dir && array[i] < array[j])) {
        std::swap(array[i], array[j]);
        colors[i] = sf::Color::Red;
        colors[j] = sf::Color::Red;
        playSound(array[i], array.size(), audioManager);
        incrementArrayAccesses(4); // Two reads and two writes for the swap
        incrementComparisons();
    } else {
        colors[i] = sf::Color::White;
        colors[j] = sf::Color::White;
        incrementComparisons();
    }
}

void BitonicSort::bitonicMerge(std::vector<int>& array, int low, int cnt, bool dir, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (cnt > 1) {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++) {
            compareAndSwap(array, i, i + k, dir, colors, audioManager);
        }
        bitonicMerge(array, low, k, dir, colors, audioManager);
        bitonicMerge(array, low + k, k, dir, colors, audioManager);
    }
}

void BitonicSort::bitonicSort(std::vector<int>& array, int low, int cnt, bool dir, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (cnt > 1) {
        int k = cnt / 2;
        bitonicSort(array, low, k, true, colors, audioManager);
        bitonicSort(array, low + k, cnt - k, false, colors, audioManager);
        bitonicMerge(array, low, cnt, dir, colors, audioManager);
    }
}

void BitonicSort::reset() {
    isSortingComplete = false;
    size = 1;
    stepIndex = 0;
    direction = true;
    comparisons = 0;
    arrayAccesses = 0;
}

bool BitonicSort::isFinished() const {
    return isSortingComplete;
}
