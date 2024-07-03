#pragma once
#include "sorting_algorithm.h"
#include <vector>
#include <list>

class StrandSort : public SortingAlgorithm {
public:
    StrandSort();

    void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) override;
    void reset() override;
    bool isFinished() const override;

private:
    enum class State {
        INITIALIZE,
        EXTRACT_STRAND,
        MERGE_STRAND,
        FINISHED
    };

    State m_state;
    std::vector<int> m_input;
    std::vector<int> m_output;
    std::list<std::vector<int>> m_strands;

    void extractStrand();
    void mergeStrands();
};
