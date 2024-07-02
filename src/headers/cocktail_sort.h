#pragma once
#include "sorting_algorithm.h"

class CocktailSort : public SortingAlgorithm {
public:
    CocktailSort() : isSortingComplete(false), start(0), end(0), swapped(true) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    bool isSortingComplete;
    int start;
    int end;
    bool swapped;
};

