#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <SFML/Audio.hpp>
#include <string>

class AudioPlayer {
public:
    AudioPlayer();
    ~AudioPlayer();

    void loadPlaylist(std::vector<std::string> files);
    void play();
    void pause();
    void stop();
    void next();
    void previous();
    bool isPlaying() const;
    void update();
    std::string getCurrentTrack() const;

private:
    std::vector<std::string> playlist;
    sf::Music currentTrack;
    size_t currentTrackIndex;
    bool playing;

    void playCurrentTrack();
    float getTrackPosition();
};

#endif
