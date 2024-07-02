#include "headers/merge_sort.h"

void MergeSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    int n = array.size();
    
    if (subarraySize < n) {
        leftStart = 0;

        while (leftStart < n - 1) {
            int mid = std::min(leftStart + subarraySize - 1, n - 1);
            int rightEnd = std::min(leftStart + 2 * subarraySize - 1, n - 1);

            for (int i = leftStart; i <= rightEnd; ++i) {
                colors[i] = sf::Color::Red;
            }

            merge(array, leftStart, mid, rightEnd, colors, audioManager);

            for (int i = leftStart; i <= rightEnd; ++i) {
                colors[i] = sf::Color::White;
            }

            leftStart += 2 * subarraySize;
        }

        subarraySize *= 2;
    } else {
        isSortingComplete = true;
    }
}

void MergeSort::merge(std::vector<int>& array, int left, int mid, int right, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftArray(n1);
    std::vector<int> rightArray(n2);

    for (int i = 0; i < n1; ++i) {
        leftArray[i] = array[left + i];
        incrementArrayAccesses(1);
    }
    for (int j = 0; j < n2; ++j) {
        rightArray[j] = array[mid + 1 + j];
        incrementArrayAccesses(1);
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        incrementComparisons();
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            colors[k] = sf::Color::Green;
            incrementArrayAccesses(1);
            playSound(array[k], array.size(), audioManager);
            i++;
        } else {
            array[k] = rightArray[j];
            colors[k] = sf::Color::Green;
            incrementArrayAccesses(1);
            playSound(array[k], array.size(), audioManager);
            j++;
        }
        k++;
    }

    while (i < n1) {
        array[k] = leftArray[i];
        colors[k] = sf::Color::Green;
        incrementArrayAccesses(1);
        playSound(array[k], array.size(), audioManager);
        i++;
        k++;
    }

    while (j < n2) {
        array[k] = rightArray[j];
        colors[k] = sf::Color::Green;
        incrementArrayAccesses(1);
        playSound(array[k], array.size(), audioManager);
        j++;
        k++;
    }
}

void MergeSort::reset() {
    isSortingComplete = false;
    subarraySize = 1;
    leftStart = 0;
    comparisons = 0;
    arrayAccesses = 0;
}

bool MergeSort::isFinished() const {
    return isSortingComplete;
}
