#include "headers/tim_sort.h"
#include <algorithm>

TimSort::TimSort() : m_state(State::FIND_RUNS), m_runIndex(0), m_mergeIndex(0) {}

void TimSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    switch (m_state) {
        case State::FIND_RUNS:
            if (m_runs.empty()) {
                findRuns(array);
                m_state = State::INSERTION_SORT;
                m_runIndex = 0;
            }
            break;

        case State::INSERTION_SORT:
            if (m_runIndex < m_runs.size()) {
                auto [start, end] = m_runs[m_runIndex];
                insertionSort(array, colors, start, end, audioManager);
                m_runIndex++;
            } else {
                m_state = State::MERGE;
                m_mergeIndex = 0;
            }
            break;

        case State::MERGE:
            if (m_runs.size() > 1) {
                size_t i = m_mergeIndex;
                size_t j = i + 1;
                if (j < m_runs.size()) {
                    merge(array, colors, m_runs[i].first, m_runs[i].second, m_runs[j].second, audioManager);
                    m_runs[i].second = m_runs[j].second;
                    m_runs.erase(m_runs.begin() + j);
                    m_mergeIndex = 0;
                } else {
                    m_mergeIndex++;
                }
            } else {
                m_state = State::FINISHED;
            }
            break;

        case State::FINISHED:
            std::fill(colors.begin(), colors.end(), sf::Color::Green);
            audioManager.stopSound();
            break;
    }
}

void TimSort::reset() {
    m_state = State::FIND_RUNS;
    m_runIndex = 0;
    m_mergeIndex = 0;
    m_runs.clear();
    m_temp.clear();
    comparisons = 0;
    arrayAccesses = 0;
}

bool TimSort::isFinished() const {
    return m_state == State::FINISHED;
}

void TimSort::findRuns(const std::vector<int>& array) {
    size_t n = array.size();
    size_t start = 0;
    while (start < n) {
        size_t end = std::min(start + RUN, n);
        m_runs.emplace_back(start, end - 1);
        start = end;
    }
}

void TimSort::insertionSort(std::vector<int>& array, std::vector<sf::Color>& colors, size_t left, size_t right, AudioManager& audioManager) {
    for (size_t i = left + 1; i <= right; i++) {
        int key = array[i];
        int j = i - 1;
        playSound(key, array.size(), audioManager);
        while (j >= left && array[j] > key) {
            array[j + 1] = array[j];
            colors[j + 1] = sf::Color::Red;
            colors[j] = sf::Color::Yellow;
            playSound(array[j], array.size(), audioManager);
            j--;
            incrementComparisons();
            incrementArrayAccesses(2);
        }
        array[j + 1] = key;
        colors[j + 1] = sf::Color::Green;
        playSound(array[j + 1], array.size(), audioManager);
        incrementArrayAccesses(1);
    }
}

void TimSort::merge(std::vector<int>& array, std::vector<sf::Color>& colors, size_t left, size_t mid, size_t right, AudioManager& audioManager) {
    size_t len1 = mid - left + 1;
    size_t len2 = right - mid;

    m_temp.resize(len1 + len2);

    for (size_t i = 0; i < len1; i++) {
        m_temp[i] = array[left + i];
        incrementArrayAccesses(2);
    }

    for (size_t i = 0; i < len2; i++) {
        m_temp[len1 + i] = array[mid + 1 + i];
        incrementArrayAccesses(2);
    }

    size_t i = 0, j = len1, k = left;

    while (i < len1 && j < len1 + len2) {
        incrementComparisons();
        playSound(m_temp[i], array.size(), audioManager);
        if (m_temp[i] <= m_temp[j]) {
            array[k] = m_temp[i];
            colors[k] = sf::Color::Red;
            i++;
        } else {
            array[k] = m_temp[j];
            colors[k] = sf::Color::Yellow;
            j++;
        }
        playSound(array[k], array.size(), audioManager);
        k++;
        incrementArrayAccesses(2);
    }

    while (i < len1) {
        array[k] = m_temp[i];
        colors[k] = sf::Color::Green;
        playSound(array[k], array.size(), audioManager);
        i++;
        k++;
        incrementArrayAccesses(2);
    }

    while (j < len1 + len2) {
        array[k] = m_temp[j];
        colors[k] = sf::Color::Green;
        playSound(array[k], array.size(), audioManager);
        j++;
        k++;
        incrementArrayAccesses(2);
    }
}