#pragma once
#include "sorting_algorithm.h"

class MergeSort : public SortingAlgorithm {
public:
    MergeSort() : isSortingComplete(false), subarraySize(1), leftStart(0) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    void merge(std::vector<int>& array, int left, int mid, int right, std::vector<sf::Color>& colors, AudioManager& audioManager);
    
    bool isSortingComplete;
    int subarraySize;
    int leftStart;
};
