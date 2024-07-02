#include "headers/audio_manager.h"

AudioManager::AudioManager() {}

void AudioManager::playSound(float frequency) {
    m_oscillator.setFrequency(frequency);
    m_oscillator.play();
}

void AudioManager::stopSound() {
    m_oscillator.stop();
}
