#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "gui.h"
#include "file_browser.h"


// ---------- GUI Class Function Definitions ---------- //

GUI::GUI(AudioPlayer& player) : audioPlayer(player) {
    createMainWindow();
}

void GUI::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void GUI::createMainWindow() {
    window.create(sf::VideoMode(600, 300), "HiRes Audio Player");

    // Background setup
    if (!backgroundTexture.loadFromFile("res/gray_background.jpg")) {
        std::cerr << "Failed to load background image!" << std::endl;
    }
    
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Load font
    if (!font.loadFromFile("/Library/Fonts/Arial Unicode.ttf")) {
        std::cout << "Error: Could not load font!" << std::endl;
    }

    // Buttons setup
    playButton = Button(sf::Vector2f(25, 50), sf::Vector2f(50, 50), "res/buttons/play_button.png");
    pauseButton = Button(sf::Vector2f(100, 50), sf::Vector2f(50, 50), "res/buttons/pause_button.png");
    stopButton = Button(sf::Vector2f(175, 50), sf::Vector2f(50, 50), "res/buttons/stop_button.png");
    prevButton = Button(sf::Vector2f(65, 125), sf::Vector2f(50, 50), "res/buttons/prev_button.png");
    nextButton = Button(sf::Vector2f(135, 125), sf::Vector2f(50, 50), "res/buttons/next_button.png");
    loadButton = Button(sf::Vector2f(400, 50), sf::Vector2f(75, 75), "res/buttons/load_button.png");

    // Text setup
    text.setFont(font);
    text.setPosition(sf::Vector2f(25, 250));
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setString("No distractions. Only music.");
}

void GUI::update() {
    audioPlayer.update();
}

void GUI::handleEvents() {
    sf::Event event;
    
    while (window.pollEvent(event)) {
        
        // Handle closing the window
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Handle window resizing

        // Handle mouse clicks
        if (event.type == sf::Event::MouseButtonPressed) {
            if (playButton.clicked(event)) {
                if (!audioPlayer.isPlaying()) {
                    audioPlayer.play();
                }
            } 
            else if (pauseButton.clicked(event)) {
                if (audioPlayer.isPlaying()) {
                    audioPlayer.pause();
                }
            }
            else if (stopButton.clicked(event)) {
                if (audioPlayer.isPlaying()) {
                    audioPlayer.stop();
                }
            }
            else if (prevButton.clicked(event)) {
                audioPlayer.previous();
            }
            else if (nextButton.clicked(event)) {
                audioPlayer.next();
            }
            else if (loadButton.clicked(event)) {
                std::vector<std::string> selectedFolder = openFolderDialog();
                if (!selectedFolder.empty()) {
                    audioPlayer.loadPlaylist(selectedFolder);
                }
            }
        }

        // Handle spacebar press
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            if (!audioPlayer.isPlaying()) {
                audioPlayer.play();
            }
            else if (audioPlayer.isPlaying()) {
                audioPlayer.pause();
            }
        }
    }
}

void GUI::render() {
    window.clear();

    window.draw(backgroundSprite);

    playButton.draw(window);
    pauseButton.draw(window);
    stopButton.draw(window);
    prevButton.draw(window);
    nextButton.draw(window);
    loadButton.draw(window);
    window.draw(text);

    window.display();
}


// ---------- Button Class Function Definitions ---------- //
Button::Button() {
}

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& imagePath) {
    texture = std::make_shared<sf::Texture>();  // Create texture using shared_ptr
    
    if (!texture->loadFromFile(imagePath)) {
        std::cerr << "Failed to load button image: " << imagePath << std::endl;
    }
    
    sprite.setTexture(*texture);  // Dereference the pointer
    sprite.setPosition(position);
    sprite.setScale(size.x / texture->getSize().x, size.y / texture->getSize().y);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Button::clicked(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (sprite.getGlobalBounds().contains(mousePos)) {
            return true;
        }
    }
    return false;
}

