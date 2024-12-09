#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "audio_player.h"
#include "gui.h"

int main() {
    AudioPlayer player;

    // Load the audio file
    if (!player.loadAudioFile("audio_files/test.wav")) {
        return -1;
    }

    GUI gui(player);
    gui.run();

    return 0;
}
