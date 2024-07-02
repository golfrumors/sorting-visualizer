#pragma once
#include "sorting_algorithm.h"

class BubbleSort : public SortingAlgorithm {
public:
    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    size_t m_i;
    size_t m_j;
    size_t m_size;
};