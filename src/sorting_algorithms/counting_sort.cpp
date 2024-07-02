#include "headers/counting_sort.h"
#include <algorithm>

void CountingSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    int max_val = *std::max_element(array.begin(), array.end());
    if (currentStep == 0) {
        count.resize(max_val + 1, 0);
        output.resize(array.size(), 0);

        for (int i = 0; i < array.size(); i++) {
            count[array[i]]++;
            incrementArrayAccesses(1);
            colors[i] = sf::Color::Red;
        }
        currentStep++;
    } else if (currentStep == 1) {
        for (int i = 1; i <= max_val; i++) {
            count[i] += count[i - 1];
            incrementArrayAccesses(1);
            colors[i % array.size()] = sf::Color::Red;
        }
        currentStep++;
    } else if (currentStep == 2) {
        for (int i = array.size() - 1; i >= 0; i--) {
            output[count[array[i]] - 1] = array[i];
            incrementArrayAccesses(2);
            colors[count[array[i]] - 1] = sf::Color::Green;
            count[array[i]]--;
            incrementArrayAccesses(1);
            playSound(array[i], array.size(), audioManager);
        }
        currentStep++;
    } else if (currentStep == 3) {
        for (int i = 0; i < array.size(); i++) {
            array[i] = output[i];
            incrementArrayAccesses(1);
            colors[i] = sf::Color::Green;
            playSound(array[i], array.size(), audioManager);
        }
        isSortingComplete = true;
    }
}

void CountingSort::reset() {
    isSortingComplete = false;
    currentStep = 0;
    comparisons = 0;
    arrayAccesses = 0;
    count.clear();
    output.clear();
}

bool CountingSort::isFinished() const {
    return isSortingComplete;
}
