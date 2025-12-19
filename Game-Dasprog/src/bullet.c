#include <ncurses.h>
#include "bullet.h"

Bullet bullets[MAX_BULLETS];

void bullet_init() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = 0;
    }
}

void bullet_spawn(int x, int y) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) {
            bullets[i].active = 1;
            bullets[i].x = x;
            bullets[i].y = y;
            break;
        }
    }
}

void bullet_update() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].x++;     

            if (bullets[i].x > COLS - 2) { 
                bullets[i].active = 0;
            }
        }
    }
}

void bullet_draw() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            mvprintw(bullets[i].y, bullets[i].x, "=>");
        }
    }
}

int bullet_check_and_clear(int x, int y) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active &&
            bullets[i].x == x &&
            bullets[i].y == y) 
        {
            bullets[i].active = 0;
            return 1;
        }
    }
    return 0;
}
