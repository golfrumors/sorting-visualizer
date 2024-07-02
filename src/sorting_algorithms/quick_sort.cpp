#include "headers/quick_sort.h"

void QuickSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (m_stack.empty() && m_left == 0 && m_right == 0) {
        m_left = 0;
        m_right = array.size() - 1;
        int p = partition(array, colors, m_left, m_right, audioManager);
        m_stack.push(std::make_pair(m_left, p - 1));
        m_stack.push(std::make_pair(p + 1, m_right));
    }

    if (!m_stack.empty()) {
        auto [left, right] = m_stack.top();
        m_stack.pop();
        if (left < right) {
            int p = partition(array, colors, left, right, audioManager);
            m_stack.push(std::make_pair(left, p - 1));
            m_stack.push(std::make_pair(p + 1, right));
        }
    }

    if (m_stack.empty()) {
        isSortingComplete = true;
        audioManager.stopSound();
    }
}

int QuickSort::partition(std::vector<int>& array, std::vector<sf::Color>& colors, int low, int high, AudioManager& audioManager) {
    int pivot = array[high];
    int i = low - 1;
    incrementArrayAccesses(1);

    for (int j = low; j < high; ++j) {
        incrementComparisons();
        colors[j] = sf::Color::Red;
        if (array[j] < pivot) {
            ++i;
            swap(array, colors, i, j);
            colors[i] = sf::Color::Green;
            playSound(array[i], array.size(), audioManager);
        } else {
            colors[j] = sf::Color::Yellow;
        }
        incrementArrayAccesses(1);
    }

    swap(array, colors, i + 1, high);
    colors[i + 1] = sf::Color::Green;
    playSound(array[i + 1], array.size(), audioManager);
    incrementArrayAccesses(2);
    
    return i + 1;
}

void QuickSort::reset() {
    while (!m_stack.empty()) {
        m_stack.pop();
    }
    m_left = 0;
    m_right = 0;
    isSortingComplete = false;
    comparisons = 0;
    arrayAccesses = 0;
}

bool QuickSort::isFinished() const {
    return isSortingComplete;
}
