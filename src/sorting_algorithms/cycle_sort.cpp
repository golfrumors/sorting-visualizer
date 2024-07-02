#include "headers/cycle_sort.h"
#include <algorithm>

void CycleSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (cycleStart == 0 && cycles == 0) {
        cycles = array.size();
    }

    if (cycleStart < cycles) {
        item = array[cycleStart];
        pos = cycleStart;

        for (int i = cycleStart + 1; i < array.size(); i++) {
            if (array[i] < item) {
                pos++;
                incrementComparisons();
            }
        }

        if (pos == cycleStart) {
            cycleStart++;
            return;
        }

        while (item == array[pos]) {
            pos++;
        }

        if (pos != cycleStart) {
            std::swap(item, array[pos]);
            colors[pos] = sf::Color::Red;
            playSound(array[pos], array.size(), audioManager);
            incrementArrayAccesses(2);
        }

        while (pos != cycleStart) {
            pos = cycleStart;

            for (int i = cycleStart + 1; i < array.size(); i++) {
                if (array[i] < item) {
                    pos++;
                    incrementComparisons();
                }
            }

            while (item == array[pos]) {
                pos++;
            }

            if (item != array[pos]) {
                std::swap(item, array[pos]);
                colors[pos] = sf::Color::Red;
                playSound(array[pos], array.size(), audioManager);
                incrementArrayAccesses(2);
            }
        }

        cycleStart++;
    } else {
        isSortingComplete = true;
        for (int i = 0; i < array.size(); ++i) {
            colors[i] = sf::Color::Green;
        }
    }
}

void CycleSort::reset() {
    isSortingComplete = false;
    cycleStart = 0;
    item = 0;
    pos = 0;
    cycles = 0;
    comparisons = 0;
    arrayAccesses = 0;
}

bool CycleSort::isFinished() const {
    return isSortingComplete;
}

