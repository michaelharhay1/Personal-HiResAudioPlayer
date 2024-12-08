#include "gui.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

GUI::GUI() {
    createMainWindow();
}

void GUI::createMainWindow() {
    window.create(sf::VideoMode(800, 600), "Audio Player");

    // Play button setup
    playButton.setSize(sf::Vector2f(100, 50));
    playButton.setPosition(50, 50);
    playButton.setFillColor(sf::Color::Green);

    // Stop button setup
    stopButton.setSize(sf::Vector2f(100, 50));
    stopButton.setPosition(200, 50);
    stopButton.setFillColor(sf::Color::Red);
}

void GUI::update() {
    // Update logic here (e.g., button states, text updates)
}

void GUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Handle mouse clicks
        if (event.type == sf::Event::MouseButtonPressed) {
            if (playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                // Play the audio when the play button is clicked
                if (!isPlaying) {
                    if (music.openFromFile("audio_files/test.wav")) {  // Change path to your audio file
                        music.play();
                        isPlaying = true;
                    } else {
                        std::cerr << "Error loading audio file" << std::endl;
                    }
                }
            } 
            else if (stopButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                // Stop the audio when the stop button is clicked
                if (isPlaying) {
                    music.stop();
                    isPlaying = false;
                }
            }
        }
    }
}

void GUI::render() {
    window.clear();
    window.draw(playButton);
    window.draw(stopButton);
    window.display();
}

void GUI::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}
