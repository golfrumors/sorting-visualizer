#pragma once
#include "sorting_algorithm.h"

class ShellSort : public SortingAlgorithm {
public:
    ShellSort() : isSortingComplete(false), gap(0), i(0), j(0) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    bool isSortingComplete;
    int gap;
    int i;
    int j;
};

