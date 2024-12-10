#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "audio_player.h"

class Button {
public:
    Button();
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& text, const sf::Font& font, const sf::Color& color);

    void draw(sf::RenderWindow& window);
    bool clicked(const sf::Event& event);

private:
    sf::RectangleShape shape;
    sf::Text buttonText;
};

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
    sf::RectangleShape divider;

    Button playButton;
    Button pauseButton;
    Button stopButton;
    Button prevButton;
    Button nextButton;
    Button loadButton;

    sf::Font font;
    sf::Text text;

    AudioPlayer& audioPlayer;
};

#endif // GUI_H
