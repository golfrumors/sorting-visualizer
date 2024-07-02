#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "audio_manager.h"

class SortingAlgorithm {
public:
    virtual ~SortingAlgorithm() = default;

    virtual void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) = 0;

    virtual void reset() = 0;

    virtual bool isFinished() const = 0;

    void playSound(int value, int arraySize, AudioManager& audioManager);

    int getComparisons() const { return comparisons; }

    int getArrayAccesses() const { return arrayAccesses; }

protected:
    void incrementComparisons() { comparisons++; }

    void incrementArrayAccesses(int count = 1) { arrayAccesses += count; }

    void swap(std::vector<int>& array, std::vector<sf::Color>& colors, int i, int j);

    int comparisons = 0;

    int arrayAccesses = 0;
};
