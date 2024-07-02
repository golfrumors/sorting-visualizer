#pragma once
#include <SFML/Audio.hpp>
#include <cmath>

class Oscillator : public sf::SoundStream {
public:
    Oscillator();
    void setFrequency(float frequency);
    void setAmplitude(float amplitude);

private:
    static constexpr unsigned SAMPLE_RATE = 44100;
    static constexpr unsigned BUFFER_SIZE = 4410;

    float m_frequency;
    float m_amplitude;
    float m_phase;

    std::vector<sf::Int16> m_samples;

    bool onGetData(Chunk& data) override;
    void onSeek(sf::Time timeOffset) override;
    void generateSamples(std::vector<sf::Int16>& samples);
};