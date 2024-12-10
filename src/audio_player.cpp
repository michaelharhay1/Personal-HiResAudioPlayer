#include "audio_player.h"
#include <SFML/Audio.hpp>
#include <iostream>

AudioPlayer::AudioPlayer() : playing(false) {}

AudioPlayer::~AudioPlayer() {}

void AudioPlayer::loadPlaylist(std::vector<std::string> files) {
    playlist = files;
    currentTrackIndex = 0;
    std::cout << "Successfully loaded " << playlist.size() << " tracks. " << std::endl;

    if (currentTrack.openFromFile(playlist[currentTrackIndex])) {
        std::cout << "Current track: " << playlist[currentTrackIndex] << std::endl;
    } 
    else {
        std::cerr << "Failed to load track: " << playlist[currentTrackIndex] << std::endl;
    }
}

void AudioPlayer::play() {
    currentTrack.play();
    playing = true;
}

void AudioPlayer::pause() {
    currentTrack.pause();
    playing = false;
}

void AudioPlayer::stop() {
    currentTrack.stop();
    playing = false;
}

void AudioPlayer::next() {
    if (currentTrackIndex + 1 < playlist.size()) {
        currentTrackIndex++;
        playCurrentTrack();
    }
}

void AudioPlayer::previous() {
    if (playing && getTrackPosition() > 5) {
        stop();
        play();
    }
    
    else if (currentTrackIndex - 1 >= 0) {
        currentTrackIndex--;
        playCurrentTrack();
    }
}

bool AudioPlayer::isPlaying() const {
    return playing;
}

void AudioPlayer::update() {
    if (playing && currentTrack.getStatus() == sf::Music::Stopped) {
        next();
    }
}

void AudioPlayer::playCurrentTrack() {
    if (currentTrackIndex < playlist.size()) {
        stop();
        playing = false;
        
        if (currentTrack.openFromFile(playlist[currentTrackIndex])) {
            currentTrack.play();
            playing = true;
            std::cout << "Now playing: " << playlist[currentTrackIndex] << std::endl;
        } 
        else {
            std::cerr << "Failed to load track: " << playlist[currentTrackIndex] << std::endl;
        }
    }
}

float AudioPlayer::getTrackPosition() {
    return currentTrack.getPlayingOffset().asSeconds();
}