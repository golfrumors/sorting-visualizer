#include "headers/cocktail_sort.h"
#include <algorithm>

void CocktailSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (end == 0) {
        end = array.size() - 1;
    }

    if (!swapped) {
        isSortingComplete = true;
        for (int i = 0; i < array.size(); ++i) {
            colors[i] = sf::Color::Green;
        }
        return;
    }

    swapped = false;

    for (int i = start; i < end; ++i) {
        if (array[i] > array[i + 1]) {
            std::swap(array[i], array[i + 1]);
            colors[i] = sf::Color::Red;
            colors[i + 1] = sf::Color::Green;
            playSound(array[i], array.size(), audioManager);
            incrementArrayAccesses(4);
            incrementComparisons();
            swapped = true;
        } else {
            colors[i] = sf::Color::White;
            colors[i + 1] = sf::Color::White;
            incrementComparisons();
        }
    }

    if (!swapped) {
        isSortingComplete = true;
        for (int i = 0; i < array.size(); ++i) {
            colors[i] = sf::Color::Green;
        }
        return;
    }

    swapped = false;
    --end;

    for (int i = end - 1; i >= start; --i) {
        if (array[i] > array[i + 1]) {
            std::swap(array[i], array[i + 1]);
            colors[i] = sf::Color::Red;
            colors[i + 1] = sf::Color::Green;
            playSound(array[i], array.size(), audioManager);
            incrementArrayAccesses(4);
            incrementComparisons();
            swapped = true;
        } else {
            colors[i] = sf::Color::White;
            colors[i + 1] = sf::Color::White;
            incrementComparisons();
        }
    }

    ++start;
}

void CocktailSort::reset() {
    isSortingComplete = false;
    start = 0;
    end = 0;
    swapped = true;
    comparisons = 0;
    arrayAccesses = 0;
}

bool CocktailSort::isFinished() const {
    return isSortingComplete;
}

