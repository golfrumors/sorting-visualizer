#include "gnome_sort.h"
#include <algorithm>

void GnomeSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (isSortingComplete) {
        for (int k = 0; k < array.size(); ++k) {
            colors[k] = sf::Color::Green;
        }
        return;
    }

    if (pos < array.size()) {
        if (pos == 0 || array[pos] >= array[pos - 1]) {
            incrementComparisons();
            colors[pos] = sf::Color::Green;
            pos++;
        } else {
            std::swap(array[pos], array[pos - 1]);
            incrementArrayAccesses(4);
            incrementComparisons();
            colors[pos] = sf::Color::Red;
            colors[pos - 1] = sf::Color::Red;
            playSound(array[pos], array.size(), audioManager);
            pos--;
        }
    } else {
        isSortingComplete = true;
        for (int k = 0; k < array.size(); ++k) {
            colors[k] = sf::Color::Green;
        }
    }

    for (int k = 0; k < array.size(); ++k) {
        if (colors[k] != sf::Color::Red && colors[k] != sf::Color::Green) {
            colors[k] = sf::Color::White;
        }
    }
}

void GnomeSort::reset() {
    isSortingComplete = false;
    pos = 0;
    comparisons = 0;
    arrayAccesses = 0;
}

bool GnomeSort::isFinished() const {
    return isSortingComplete;
}

