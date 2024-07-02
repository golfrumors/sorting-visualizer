#pragma once
#include "sorting_algorithm.h"
#include <list>

class StrandSort : public SortingAlgorithm {
public:
    StrandSort() : isSortingComplete(false), currentIndex(0), phase(0) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    bool isSortingComplete;
    int currentIndex;
    int phase; // 0 - extracting sublist, 1 - merging sublist
    std::list<int> output;
    std::list<int> sublist;

    void extractSublist(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager);
    void merge(std::list<int>& output, std::list<int>& sublist);
};
