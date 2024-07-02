#pragma once
#include "sorting_algorithm.h"
#include <vector>

class PigeonholeSort : public SortingAlgorithm {
public:
    PigeonholeSort() : isSortingComplete(false), minVal(0), maxVal(0), currentHole(0), currentIndex(0) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    bool isSortingComplete;
    int minVal;
    int maxVal;
    int currentHole;
    int currentIndex;
    std::vector<int> pigeonholes;
};

