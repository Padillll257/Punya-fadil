#include "game.h"
#include "audio.h"
#include "game_state.h"

int main() {
    audio_init();         
    init_game_state();     
    game_init();           
    game_loop();
    game_end();           
    audio_quit();         

    return 0;
}
