#pragma once
#include "sorting_algorithm.h"
#include <stack>

class QuickSort : public SortingAlgorithm {
public:
    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    int partition(std::vector<int>& array, std::vector<sf::Color>& colors, int low, int high, AudioManager& audioManager);
    
    std::stack<std::pair<int, int>> m_stack;
    int m_left;
    int m_right;
    int m_partitionIndex;
    bool m_isPartitioning;
    size_t m_size;
    bool isSortingComplete;
};