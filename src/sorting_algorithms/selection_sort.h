#pragma once
#include "sorting_algorithm.h"

class SelectionSort : public SortingAlgorithm {
public:
    SelectionSort() : m_sortingIndex(0), m_currentIndex(1), m_minIndex(0), m_size(0), isSortingComplete(false) {}
    
    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    size_t m_sortingIndex;
    size_t m_currentIndex;
    size_t m_minIndex;
    size_t m_size;
    bool isSortingComplete;
};