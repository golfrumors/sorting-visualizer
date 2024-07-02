#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "../audio/audio_manager.h"

class SortingAlgorithm {
public:
    virtual ~SortingAlgorithm() = default;

    virtual void step(std::vector<int>& array, std::vector<sf::Color>& colors, AudioManager& audioManager) = 0;

    virtual void reset() = 0;

    virtual bool isFinished() const = 0;

    void playSound(int value, int arraySize, AudioManager& audioManager);

protected:
    void swap(std::vector<int>& array, std::vector<sf::Color>& colors, int i, int j);
};