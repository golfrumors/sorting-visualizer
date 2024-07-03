#pragma once
#include "sorting_algorithm.h"
#include <vector>

class BogoSort : public SortingAlgorithm {
public:
    BogoSort() : isSortingComplete(false) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    bool isSorted(const std::vector<int>& array);
    void shuffle(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager);
    bool isSortingComplete;
};

