#include "audio_player.h"
#include <SFML/Audio.hpp>
#include <iostream>

AudioPlayer::AudioPlayer() {}

AudioPlayer::~AudioPlayer() {}

bool AudioPlayer::loadAudioFile(const std::string& filename) {
    if (!buffer.loadFromFile(filename)) {
        std::cerr << "Error loading audio file!" << std::endl;
        return false;
    }
    sound.setBuffer(buffer);
    return true;
}

void AudioPlayer::play() {
    sound.play();
}

void AudioPlayer::pause() {
    sound.pause();
}

void AudioPlayer::stop() {
    sound.stop();
}

bool AudioPlayer::isPlaying() const {
    return sound.getStatus() == sf::Sound::Playing;
}