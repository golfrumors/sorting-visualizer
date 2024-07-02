#include "headers/radix_sort.h"
#include <algorithm>
#include <cmath>

void RadixSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (currentStep == 0) {
        maxVal = *std::max_element(array.begin(), array.end());
        exp = 1;
        currentStep++;
    } else if (exp <= maxVal) {
        countingSort(array, colors, audioManager);
        exp *= 10;
        currentStep++;
    } else {
        isSortingComplete = true;
        for (int i = 0; i < array.size(); ++i) {
            colors[i] = sf::Color::Green;
        }
    }
}

void RadixSort::countingSort(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    int n = array.size();
    output.resize(n);
    count.assign(10, 0);

    for (int i = 0; i < n; ++i) {
        int index = (array[i] / exp) % 10;
        count[index]++;
        incrementArrayAccesses(1);
        colors[i] = sf::Color::Red;
    }

    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
        incrementArrayAccesses(1);
    }

    for (int i = n - 1; i >= 0; --i) {
        int index = (array[i] / exp) % 10;
        output[count[index] - 1] = array[i];
        incrementArrayAccesses(2);
        colors[count[index] - 1] = sf::Color::Green;
        playSound(array[i], array.size(), audioManager);
        count[index]--;
        incrementArrayAccesses(1);
    }

    for (int i = 0; i < n; ++i) {
        array[i] = output[i];
        incrementArrayAccesses(1);
        colors[i] = sf::Color::Green;
        playSound(array[i], array.size(), audioManager);
    }
}

void RadixSort::reset() {
    isSortingComplete = false;
    currentStep = 0;
    exp = 1;
    maxVal = 0;
    comparisons = 0;
    arrayAccesses = 0;
    count.clear();
    output.clear();
}

bool RadixSort::isFinished() const {
    return isSortingComplete;
}
