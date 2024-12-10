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

    // Load font
    if (!font.loadFromFile("/Library/Fonts/Arial Unicode.ttf")) {
        std::cerr << "Error: Could not load font!" << std::endl;
    }

    // Buttons setup
    playButton = Button(sf::Vector2f(25, 50), sf::Vector2f(50, 50), "Play", font, sf::Color::Green);
    pauseButton = Button(sf::Vector2f(100, 50), sf::Vector2f(50, 50), "Pause", font, sf::Color::Yellow);
    stopButton = Button(sf::Vector2f(175, 50), sf::Vector2f(50, 50), "Stop", font, sf::Color::Red);
    prevButton = Button(sf::Vector2f(65, 125), sf::Vector2f(50, 50), "<<", font, sf::Color(0x9A9A9AFF));
    nextButton = Button(sf::Vector2f(135, 125), sf::Vector2f(50, 50), ">>", font, sf::Color(0x9A9A9AFF));
    loadButton = Button(sf::Vector2f(400, 50), sf::Vector2f(100, 25), "Load audio...", font, sf::Color(0x9A9A9AFF));

    // Divider setup
    divider.setSize(sf::Vector2f(5, window.getSize().y));
    divider.setPosition((window.getSize().x) / 2, 0);
    divider.setFillColor(sf::Color(0x9A9A9AFF));

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

    playButton.draw(window);
    pauseButton.draw(window);
    stopButton.draw(window);
    prevButton.draw(window);
    nextButton.draw(window);
    loadButton.draw(window);
    window.draw(divider);
    window.draw(text);

    window.display();
}


// ---------- Button Class Function Definitions ---------- //
Button::Button() {
}

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::String& text, const sf::Font& font, const sf::Color& color) {
    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(color);

    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(16);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setOutlineColor(sf::Color::Black);
    buttonText.setOutlineThickness(0.4);

    // Center the text in the button
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    buttonText.setPosition(position.x + size.x / 2, position.y + size.y / 2);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(buttonText);
}

bool Button::clicked(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (shape.getGlobalBounds().contains(mousePos)) {
            return true;
        }
    }
    return false;
}

