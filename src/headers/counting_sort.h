#pragma once
#include "headers/sorting_algorithm.h"

class CountingSort : public SortingAlgorithm {
public:
    CountingSort() : isSortingComplete(false), currentStep(0) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    bool isSortingComplete;
    int currentStep;
    std::vector<int> count;
    std::vector<int> output;
};
