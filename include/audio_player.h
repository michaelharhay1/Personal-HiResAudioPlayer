#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <SFML/Audio.hpp>
#include <string>

class AudioPlayer {
public:
    AudioPlayer();
    ~AudioPlayer();

    bool loadAudioFile(const std::string& filename);
    void play();
    void pause();
    void stop();
    bool isPlaying() const;

private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
};

#endif // AUDIO_PLAYER_H
