#include "headers/shell_sort.h"
#include <algorithm>

void ShellSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (gap == 0) {
        gap = array.size() / 2;
        i = gap;
        j = i;
    }

    if (gap > 0) {
        if (i < array.size()) {
            if (j >= gap && array[j - gap] > array[j]) {
                std::swap(array[j], array[j - gap]);
                incrementArrayAccesses(4);
                incrementComparisons();
                colors[j] = sf::Color::Green;
                colors[j - gap] = sf::Color::Red;
                playSound(array[j], array.size(), audioManager);
                j -= gap;
            } else {
                incrementComparisons();
                colors[j] = sf::Color::White;
                i++;
                j = i;
            }
        } else {
            gap /= 2;
            i = gap;
            j = i;
        }
    } else {
        isSortingComplete = true;
        for (int k = 0; k < array.size(); ++k) {
            colors[k] = sf::Color::Green;
        }
    }
}

void ShellSort::reset() {
    isSortingComplete = false;
    gap = 0;
    i = 0;
    j = 0;
    comparisons = 0;
    arrayAccesses = 0;
}

bool ShellSort::isFinished() const {
    return isSortingComplete;
}
