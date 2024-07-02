#include "headers/bucket_sort.h"
#include <algorithm>

void BucketSort::step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) {
    if (currentBucket == 0 && currentElement == 0) {
        maxVal = *std::max_element(array.begin(), array.end());
        buckets.resize(array.size());

        for (int i = 0; i < array.size(); ++i) {
            int bucketIndex = array[i] * array.size() / (maxVal + 1);
            buckets[bucketIndex].push_back(array[i]);
            incrementArrayAccesses(1);
            colors[i] = sf::Color::Red;
        }
        currentBucket++;
    } else if (currentBucket <= array.size()) {
        if (currentElement < buckets[currentBucket - 1].size()) {
            sortBucket(buckets[currentBucket - 1]);
            currentElement++;
        } else {
            currentElement = 0;
            currentBucket++;
        }
    } else {
        int index = 0;
        for (int i = 0; i < buckets.size(); ++i) {
            for (int j = 0; j < buckets[i].size(); ++j) {
                array[index] = buckets[i][j];
                incrementArrayAccesses(1);
                colors[index] = sf::Color::Green;
                playSound(array[index], array.size(), audioManager);
                index++;
            }
        }
        isSortingComplete = true;
    }
}

void BucketSort::sortBucket(std::vector<int>& bucket) {
    std::sort(bucket.begin(), bucket.end());
    incrementArrayAccesses(bucket.size());
}

void BucketSort::reset() {
    isSortingComplete = false;
    currentBucket = 0;
    currentElement = 0;
    maxVal = 0;
    comparisons = 0;
    arrayAccesses = 0;
    buckets.clear();
    output.clear();
}

bool BucketSort::isFinished() const {
    return isSortingComplete;
}
