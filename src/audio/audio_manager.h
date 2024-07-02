#pragma once
#include "oscillator.h"

class AudioManager {
public:
    AudioManager();
    void playSound(float frequency);
    void stopSound();

private:
    Oscillator m_oscillator;
};