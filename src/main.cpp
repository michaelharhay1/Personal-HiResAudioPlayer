#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "audio_player.h"
#include "gui.h"

int main() {
    
    // Init AudioPlayer and GUI objects
    AudioPlayer player;
    GUI gui;

    // Load audio file, return error if failed
    if (!player.loadAudioFile("audio_files/test.wav")) {
        return -1;
    }

    // Run the GUI
    gui.run();

    return 0;
}
