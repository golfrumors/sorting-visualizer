#include "headers/pigeonhole_sort.h"
#include <algorithm>
#include <limits>

void PigeonholeSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (!pigeonholes.empty() && currentHole <= maxVal - minVal) {
        while (pigeonholes[currentHole] > 0) {
            array[currentIndex] = minVal + currentHole;
            colors[currentIndex] = sf::Color::Red;
            playSound(array[currentIndex], array.size(), audioManager);
            incrementArrayAccesses(1);
            currentIndex++;
            pigeonholes[currentHole]--;
        }
        currentHole++;
        if (currentHole > maxVal - minVal) {
            isSortingComplete = true;
            for (int i = 0; i < array.size(); ++i) {
                colors[i] = sf::Color::Green;
            }
        }
        return;
    }

    if (pigeonholes.empty()) {
        minVal = *std::min_element(array.begin(), array.end());
        maxVal = *std::max_element(array.begin(), array.end());
        incrementArrayAccesses(2 * array.size());

        pigeonholes.resize(maxVal - minVal + 1, 0);
        for (int i = 0; i < array.size(); ++i) {
            pigeonholes[array[i] - minVal]++;
            incrementArrayAccesses(1);
        }

        currentHole = 0;
        currentIndex = 0;
    }
}

void PigeonholeSort::reset() {
    isSortingComplete = false;
    minVal = 0;
    maxVal = 0;
    currentHole = 0;
    currentIndex = 0;
    pigeonholes.clear();
    comparisons = 0;
    arrayAccesses = 0;
}

bool PigeonholeSort::isFinished() const {
    return isSortingComplete;
}

