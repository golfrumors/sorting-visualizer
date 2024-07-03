#pragma once
#include "sorting_algorithm.h"

class BitonicSort : public SortingAlgorithm {
public:
    BitonicSort() : isSortingComplete(false), size(1), stepIndex(0), direction(true) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    bool isSortingComplete;
    int size;
    int stepIndex;
    bool direction;

    void bitonicMerge(std::vector<int>& array, int low, int cnt, bool dir, std::vector<sf::Color>& colors, AudioManager& audioManager);
    void bitonicSort(std::vector<int>& array, int low, int cnt, bool dir, std::vector<sf::Color>& colors, AudioManager& audioManager);
    void compareAndSwap(std::vector<int>& array, int i, int j, bool dir, std::vector<sf::Color>& colors, AudioManager& audioManager);
};
