#pragma once
#include "sorting_algorithm.h"
#include <vector>

class PancakeSort : public SortingAlgorithm {
public:
    PancakeSort() : i(0), isSortingComplete(false) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    int i;
    bool isSortingComplete;

    void flip(std::vector<int>& array, int k, std::vector<sf::Color>& colors, AudioManager& audioManager);
    int findMax(std::vector<int>& array, int n, std::vector<sf::Color>& colors);
};

