#include "oscillator.h"

Oscillator::Oscillator() 
    : m_frequency(440.f), m_amplitude(0.5f), m_phase(0.f) {
    m_samples.resize(BUFFER_SIZE);
    initialize(1, SAMPLE_RATE);
}

void Oscillator::setFrequency(float frequency) {
    m_frequency = std::min(frequency, 880.f);
}

void Oscillator::setAmplitude(float amplitude) {
    m_amplitude = amplitude;
}

bool Oscillator::onGetData(Chunk& data) {
    generateSamples(m_samples);
    data.samples = m_samples.data();
    data.sampleCount = m_samples.size();
    return true;
}

void Oscillator::onSeek(sf::Time timeOffset) {
    m_phase = 0.f;
}

void Oscillator::generateSamples(std::vector<sf::Int16>& samples) {
    const float twoPI = 2.f * 3.14159265358979323846f;
    const float increment = m_frequency / SAMPLE_RATE;

    for (std::size_t i = 0; i < BUFFER_SIZE; ++i) {
        samples[i] = static_cast<sf::Int16>(m_amplitude * 32767.f * std::sin(m_phase * twoPI));
        m_phase += increment;
        m_phase -= static_cast<int>(m_phase);
    }
}
