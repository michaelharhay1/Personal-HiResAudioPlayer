#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "audio_player.h"

class GUI {
public:
    GUI();
    void run();

private:
    void createMainWindow();
    void update();
    void handleEvents();
    void render();
    
    sf::RenderWindow window;
    sf::RectangleShape playButton;
    sf::RectangleShape stopButton;

    AudioPlayer player;

    sf::Music music;
    bool isPlaying = false;
};

#endif // GUI_H
