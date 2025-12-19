#ifndef GAME_H
#define GAME_H

typedef enum {
    GAME_RUNNING,
    GAME_WIN,
    GAME_LOSE
} GameState;

void game_init();
void game_loop();
void game_end();

#endif
