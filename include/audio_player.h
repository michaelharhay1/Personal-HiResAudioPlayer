#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <SFML/Audio.hpp>
#include <string>

class AudioPlayer {
public:
    AudioPlayer();
    ~AudioPlayer();

    bool loadAudioFile(const std::string& filepath);
    void play();
    void pause();
    void stop();
    bool isPlaying() const;

private:
    sf::Music music;
    bool playing = false;
};

#endif
