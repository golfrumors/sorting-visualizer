#include "selection_sort.h"
#include <algorithm>

void SelectionSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    m_size = array.size();
    
    if (m_sortingIndex < m_size - 1) {
        colors[m_sortingIndex] = sf::Color::Red;
        
        if (m_currentIndex < array.size()) {
            colors[m_currentIndex] = sf::Color::Yellow;
            
            if (array[m_currentIndex] < array[m_minIndex]) {
                colors[m_minIndex] = sf::Color::White;
                m_minIndex = m_currentIndex;
                colors[m_minIndex] = sf::Color::Red;
            }
            
            m_currentIndex++;
        } else {
            if (m_minIndex != m_sortingIndex) {
                swap(array, colors, m_sortingIndex, m_minIndex);
                playSound(array[m_sortingIndex], array.size(), audioManager);
            }
            
            colors[m_sortingIndex] = sf::Color::Green;
            m_sortingIndex++;
            m_currentIndex = m_sortingIndex + 1;
            m_minIndex = m_sortingIndex;
        }
    }

    if(isFinished())
        audioManager.stopSound();
}

void SelectionSort::reset() {
    m_sortingIndex = 0;
    m_currentIndex = 1;
    m_minIndex = 0;
    m_size = 0;
}

bool SelectionSort::isFinished() const {
    return m_sortingIndex >= m_size - 1;
}