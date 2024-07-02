#pragma once
#include "sorting_algorithm.h"

class CombSort : public SortingAlgorithm {
public:
    CombSort() : isSortingComplete(false), gap(0), i(0), swapped(false) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    bool isSortingComplete;
    int gap;
    int i;
    bool swapped;
};

