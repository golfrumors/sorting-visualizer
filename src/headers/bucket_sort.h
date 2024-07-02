#pragma once
#include "sorting_algorithm.h"
#include <vector>

class BucketSort : public SortingAlgorithm {
public:
    BucketSort() : isSortingComplete(false), currentBucket(0), currentElement(0), maxVal(0) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    bool isSortingComplete;
    int currentBucket;
    int currentElement;
    int maxVal;
    std::vector<std::vector<int>> buckets;
    std::vector<int> output;

    void sortBucket(std::vector<int>& bucket);
};
