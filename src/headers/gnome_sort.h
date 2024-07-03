#pragma once
#include "sorting_algorithm.h"
#include <vector>

class GnomeSort : public SortingAlgorithm {
public:
    GnomeSort() : pos(0), isSortingComplete(false) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    int pos;
    bool isSortingComplete;
};

