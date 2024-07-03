#include "headers/strand_sort.h"

StrandSort::StrandSort() : m_state(State::INITIALIZE) {}

void StrandSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    switch (m_state) {
        case State::INITIALIZE:
            if (!array.empty()) {
                m_input.assign(array.begin(), array.end());
                m_output.clear();
                m_state = State::EXTRACT_STRAND;
            } else {
                m_state = State::FINISHED;
            }
            break;

        case State::EXTRACT_STRAND:
            if (!m_input.empty()) {
                extractStrand();
                if (m_strands.back().size() > 1) { // Ensure there's meaningful data to merge
                    m_state = State::MERGE_STRAND;
                } else {
                    m_strands.pop_back(); // Remove ineffective strand
                }
            } else {
                m_state = State::FINISHED; // No more input to process
            }
            break;

        case State::MERGE_STRAND:
            mergeStrands();
            m_state = State::EXTRACT_STRAND; // Return to extract next strand
            break;

        case State::FINISHED:
            array = m_output;  // Assign sorted output to original array
            std::fill(colors.begin(), colors.end(), sf::Color::Green); // Indicate completion
            audioManager.stopSound();
            break;
    }
}

void StrandSort::reset() {
    m_state = State::INITIALIZE;
    m_input.clear();
    m_output.clear();
    m_strands.clear();
}

bool StrandSort::isFinished() const {
    return m_state == State::FINISHED;
}

void StrandSort::extractStrand() {
    std::vector<int> strand;
    int last = m_input.front();
    strand.push_back(last);
    auto it = m_input.begin() + 1;

    while (it != m_input.end()) {
        if (*it >= last) {
            last = *it;
            strand.push_back(last);
            it = m_input.erase(it);
        } else {
            ++it;
        }
    }

    if (!strand.empty()) {
        m_strands.push_back(strand);
    }
}

void StrandSort::mergeStrands() {
    if (m_strands.empty()) return;

    std::vector<int> temp;
    auto it_strand = m_strands.front().begin();
    auto it_output = m_output.begin();

    while (it_strand != m_strands.front().end() && it_output != m_output.end()) {
        if (*it_strand < *it_output) {
            temp.push_back(*it_strand++);
        } else {
            temp.push_back(*it_output++);
        }
    }

    // Append remaining elements from both vectors
    while (it_strand != m_strands.front().end()) {
        temp.push_back(*it_strand++);
    }
    while (it_output != m_output.end()) {
        temp.push_back(*it_output++);
    }

    m_output = temp;
    m_strands.pop_front();
}
