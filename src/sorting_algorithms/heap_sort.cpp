#include "headers/heap_sort.h"

void HeapSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (heapSize == 0) {
        heapSize = array.size();

        for (int i = heapSize / 2 - 1; i >= 0; i--) {
            heapify(array, heapSize, i, colors, audioManager);
        }
    }

    if (heapSize > 1) {
        swap(array, colors, 0, heapSize - 1);
        playSound(array[heapSize - 1], array.size(), audioManager);
        heapSize--;
        heapify(array, heapSize, 0, colors, audioManager);
    } else {
        isSortingComplete = true;
    }
}

void HeapSort::heapify(std::vector<int>& array, int n, int i, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    incrementComparisons();
    colors[i] = sf::Color::Red;
    if (left < n && array[left] > array[largest]) {
        largest = left;
        incrementArrayAccesses(2);
    }

    incrementComparisons();
    if (right < n && array[right] > array[largest]) {
        largest = right;
        incrementArrayAccesses(2);
    }

    if (largest != i) {
        swap(array, colors, i, largest);
        playSound(array[i], array.size(), audioManager);
        heapify(array, n, largest, colors, audioManager);
    }
}

void HeapSort::reset() {
    isSortingComplete = false;
    heapSize = 0;
    comparisons = 0;
    arrayAccesses = 0;
}

bool HeapSort::isFinished() const {
    return isSortingComplete;
}
