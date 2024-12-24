#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <filesystem>
#include "audio_player.h"

class Button {
public:
    Button();
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& imagePath);

    void draw(sf::RenderWindow& window);
    bool clicked(const sf::Event& event);
    void update(const sf::RenderWindow& window);

private:
    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;
    bool isHovered = false;

    sf::Color normalColor{255, 255, 255, 255};
    sf::Color hoverColor{200, 200, 200, 255};
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
    std::string parseTitle(const std::string& filePath);
    
    sf::RenderWindow window;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

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
