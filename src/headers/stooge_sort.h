#pragma once
#include "sorting_algorithm.h"
#include <vector>

class StoogeSort : public SortingAlgorithm {
public:
    StoogeSort() : isSortingComplete(false), l(0), h(0), stage(0) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    bool isSortingComplete;
    int l, h, stage;
    std::vector<std::pair<int, int>> stack;

    void stoogeSortStep(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager);
};
