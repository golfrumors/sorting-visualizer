#include "headers/strand_sort.h"
#include <algorithm>
#include <vector>

void StrandSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (isSortingComplete) {
        for (int i = 0; i < array.size(); ++i) {
            colors[i] = sf::Color::Green;
        }
        return;
    }

    if (phase == 0) { // Extracting sublist
        extractSublist(array, colors, audioManager);
        if (sublist.empty()) {
            isSortingComplete = true;
            return;
        }
        phase = 1;
    } else if (phase == 1) { // Merging sublist
        merge(output, sublist);
        sublist.clear();
        phase = 0;

        // Update the array with the sorted output
        int index = 0;
        for (auto& elem : output) {
            array[index] = elem;
            colors[index] = sf::Color::White;
            playSound(array[index], array.size(), audioManager);
            incrementArrayAccesses(1);
            index++;
        }

        if (currentIndex == array.size()) {
            isSortingComplete = true;
            for (int i = 0; i < array.size(); ++i) {
                colors[i] = sf::Color::Green;
            }
        }
    }
}

void StrandSort::extractSublist(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    sublist.clear();
    if (currentIndex < array.size()) {
        sublist.push_back(array[currentIndex]);
        colors[currentIndex] = sf::Color::Red;
        playSound(array[currentIndex], array.size(), audioManager);
        incrementArrayAccesses(1);

        int i = currentIndex + 1;
        while (i < array.size()) {
            if (array[i] >= sublist.back()) {
                sublist.push_back(array[i]);
                colors[i] = sf::Color::Red;
                playSound(array[i], array.size(), audioManager);
                incrementArrayAccesses(1);
            }
            i++;
        }

        // Remove elements of the sublist from the array
        array.erase(std::remove_if(array.begin() + currentIndex, array.end(),
            [this](int value) {
                return std::find(sublist.begin(), sublist.end(), value) != sublist.end();
            }), array.end());
    }
}

void StrandSort::merge(std::list<int>& output, std::list<int>& sublist) {
    auto it1 = output.begin();
    auto it2 = sublist.begin();

    while (it1 != output.end() && it2 != sublist.end()) {
        if (*it1 <= *it2) {
            ++it1;
        } else {
            it1 = output.insert(it1, *it2);
            ++it2;
        }
        incrementComparisons();
    }

    while (it2 != sublist.end()) {
        output.push_back(*it2);
        ++it2;
    }
}

void StrandSort::reset() {
    isSortingComplete = false;
    currentIndex = 0;
    phase = 0;
    output.clear();
    sublist.clear();
    comparisons = 0;
    arrayAccesses = 0;
}

bool StrandSort::isFinished() const {
    return isSortingComplete;
}
