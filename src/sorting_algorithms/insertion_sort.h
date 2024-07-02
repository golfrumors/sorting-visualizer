#pragma once
#include "sorting_algorithm.h"

class InsertionSort : public SortingAlgorithm {
public:
    InsertionSort() : i(1), j(0), isSortingComplete(false) {}
    
    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    int i;
    int j;
    bool isSortingComplete;
    int key;
};
