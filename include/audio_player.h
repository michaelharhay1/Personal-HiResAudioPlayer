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

private:
    std::vector<std::string> playlist;
    sf::Music currentTrack;
    size_t currentTrackIndex;
    bool playing = false;
    bool paused = false;

    void playCurrentTrack();
    float getTrackPosition();
};

#endif
