#include "sorting_algorithm.h"
#include <algorithm>

void SortingAlgorithm::playSound(int value, int arraySize, AudioManager& audioManager) {
    float frequency = 100.f + (static_cast<float>(value) * 900.f / arraySize);
    audioManager.playSound(frequency);
}

void SortingAlgorithm::swap(std::vector<int>& array, std::vector<sf::Color>& colors, int i, int j) {
    std::swap(array[i], array[j]);
    std::swap(colors[i], colors[j]);
    incrementArrayAccesses(4);
}
