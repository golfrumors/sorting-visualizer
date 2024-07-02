#include "bubble_sort.h"
#include <algorithm>

void BubbleSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    m_size = array.size();
    if (m_i < m_size - 1) {
        if (m_j < m_size - m_i - 1) {
            incrementComparisons();
            colors[m_j] = sf::Color::Red;
            colors[m_j + 1] = sf::Color::Red;

            if (array[m_j] > array[m_j + 1]) {
                swap(array, colors, m_j, m_j + 1);
                playSound(array[m_j], m_size, audioManager);
            }

            m_j++;
        } else {
            colors[m_size - m_i - 1] = sf::Color::Green;
            m_i++;
            m_j = 0;
        }
    } else {
        colors[0] = sf::Color::Green;
        isSortingComplete = true;
    }
    if(isFinished())
        audioManager.stopSound();
}

void BubbleSort::reset() {
    m_i = 0;
    m_j = 0;
    m_size = 0;
    isSortingComplete = false;
    comparisons = 0;
    arrayAccesses = 0;
}

bool BubbleSort::isFinished() const {
    return m_i >= m_size - 1;
}
