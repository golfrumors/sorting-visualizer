#pragma once
#include "sorting_algorithm.h"
#include <vector>

class TimSort : public SortingAlgorithm {
public:
    TimSort();
    
    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    static const int RUN = 32;
    
    enum class State {
        FIND_RUNS,
        INSERTION_SORT,
        MERGE,
        FINISHED
    };

    State m_state;
    size_t m_runIndex;
    size_t m_mergeIndex;
    std::vector<std::pair<size_t, size_t>> m_runs;
    std::vector<int> m_temp;

    void findRuns(const std::vector<int>& array);
    void insertionSort(std::vector<int>& array, std::vector<sf::Color>& colors, size_t left, size_t right, AudioManager& audioManager);
    void merge(std::vector<int>& array, std::vector<sf::Color>& colors, size_t left, size_t mid, size_t right, AudioManager& audioManager);
};