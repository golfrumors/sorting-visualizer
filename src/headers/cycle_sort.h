#pragma once
#include "sorting_algorithm.h"

class CycleSort : public SortingAlgorithm {
public:
    CycleSort() : isSortingComplete(false), cycleStart(0), item(0), pos(0), cycles(0) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    bool isSortingComplete;
    int cycleStart;
    int item;
    int pos;
    int cycles;
};

