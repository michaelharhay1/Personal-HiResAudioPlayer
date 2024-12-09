#include "gui.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

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
    window.create(sf::VideoMode(800, 600), "HiRes Audio Player");

    // Play button setup
    playButton.setSize(sf::Vector2f(50, 50));
    playButton.setPosition(50, 50);
    playButton.setFillColor(sf::Color::Green);

    // Pause button setup
    pauseButton.setSize(sf::Vector2f(50, 50));
    pauseButton.setPosition(150, 50);
    pauseButton.setFillColor(sf::Color::Yellow);

    // Stop button setup
    stopButton.setSize(sf::Vector2f(50, 50));
    stopButton.setPosition(250, 50);
    stopButton.setFillColor(sf::Color::Red);
}

void GUI::update() {
    // Update logic here (e.g., button states, text updates)
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
            
            // Play button is clicked
            if (playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                if (!audioPlayer.isPlaying()) {
                    audioPlayer.play();
                }
            } 

            // Pause button is clicked
            else if (pauseButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                if (audioPlayer.isPlaying()) {
                    audioPlayer.pause();
                }
            }

            // Stop button is clicked
            else if (stopButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                if (audioPlayer.isPlaying()) {
                    audioPlayer.stop();
                }
            }
        }
    }
}

void GUI::render() {
    window.clear();
    window.draw(playButton);
    window.draw(pauseButton);
    window.draw(stopButton);
    window.display();
}
