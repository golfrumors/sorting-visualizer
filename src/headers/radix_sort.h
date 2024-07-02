#pragma once
#include "sorting_algorithm.h"

class RadixSort : public SortingAlgorithm {
public:
    RadixSort() : isSortingComplete(false), currentStep(0), exp(1), maxVal(0) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    bool isSortingComplete;
    int currentStep;
    int exp;
    int maxVal;
    std::vector<int> count;
    std::vector<int> output;

    void countingSort(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager);
};
