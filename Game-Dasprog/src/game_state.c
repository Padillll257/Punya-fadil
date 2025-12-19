#include "game_state.h"

int CURRENT_STAGE = 1;

void init_game_state() {
    CURRENT_STAGE = 1;
}

void next_stage() {
    CURRENT_STAGE++;
}

void reset_stage() {
    CURRENT_STAGE = 1;
}
