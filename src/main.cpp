#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "audio_player.h"
#include "gui.h"

int main() {
    AudioPlayer player;
    GUI gui(player);
    gui.run();

    return 0;
}
