#include "audio_player.h"
#include <SFML/Audio.hpp>
#include <iostream>

AudioPlayer::AudioPlayer() {}

AudioPlayer::~AudioPlayer() {}

bool AudioPlayer::loadAudioFile(const std::string& filepath) {
    if (!music.openFromFile(filepath)) {
        std::cerr << "Error loading audio file!" << std::endl;
        return false;
    }
    return true;
}

void AudioPlayer::play() {
    music.play();
    playing = true;
}

void AudioPlayer::pause() {
    music.pause();
    playing = false;
}

void AudioPlayer::stop() {
    music.stop();
    playing = false;
}

bool AudioPlayer::isPlaying() const {
    return playing;
}