#pragma once
#include "sorting_algorithm.h"

class BubbleSort : public SortingAlgorithm {
public:
    BubbleSort() : m_i(0), m_j(0), isSortingComplete(false) {}

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    size_t m_i;
    size_t m_j;
    size_t m_size;
    bool isSortingComplete;
};