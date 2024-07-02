#pragma once
#include "sorting_algorithm.h"

class HeapSort : public SortingAlgorithm {
public:
    HeapSort() : isSortingComplete(false), heapSize(0) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    void heapify(std::vector<int>& array, int n, int i, std::vector<sf::Color>& colors, AudioManager& audioManager);
    
    bool isSortingComplete;
    int heapSize;
};
