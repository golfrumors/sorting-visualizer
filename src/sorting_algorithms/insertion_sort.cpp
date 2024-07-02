#include "headers/insertion_sort.h"

void InsertionSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (i < array.size()) {
        key = array[i];
        incrementArrayAccesses(1);
        j = i - 1;

        colors[i] = sf::Color::Red;

        while (j >= 0 && array[j] > key) {
            incrementComparisons();
            array[j + 1] = array[j];
            incrementArrayAccesses(2);
            colors[j + 1] = sf::Color::Green;
            playSound(array[j + 1], array.size(), audioManager);
            --j;
        }
        array[j + 1] = key;
        incrementArrayAccesses(1);
        colors[j + 1] = sf::Color::Green;
        playSound(array[j + 1], array.size(), audioManager);
        ++i;
    } else {
        for (int k = 0; k < array.size(); ++k) {
            colors[k] = sf::Color::Green;
        }
        isSortingComplete = true;
    }
}

void InsertionSort::reset() {
    i = 1;
    j = 0;
    isSortingComplete = false;
    comparisons = 0;
    arrayAccesses = 0;
}

bool InsertionSort::isFinished() const {
    return isSortingComplete;
}
