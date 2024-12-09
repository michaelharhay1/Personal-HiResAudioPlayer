#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "audio_player.h"

class GUI {
public:
    GUI(AudioPlayer& player);
    void run();

private:
    void createMainWindow();
    void update();
    void handleEvents();
    void render();
    
    sf::RenderWindow window;
    sf::RectangleShape playButton;
    sf::RectangleShape pauseButton;
    sf::RectangleShape stopButton;

    AudioPlayer& audioPlayer;
};

#endif // GUI_H
