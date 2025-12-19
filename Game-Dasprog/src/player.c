#include <ncurses.h>
#include "player.h"
#include "bullet.h"

void player_init(Player *p) {
    p->x = 10;
    p->y = 10;

    p->max_hp = 40;
    p->hp = 40;

    p->damage = 3;
    p->speed = 1;

    p->width  = 5;
    p->height = 4;

}

void player_update(Player *p, int input) {
    int s = p->speed;

    if (input == KEY_UP    || input == 'w') p->y -= s;
    if (input == KEY_DOWN  || input == 's') p->y += s;
    if (input == KEY_LEFT  || input == 'a') p->x -= s;
    if (input == KEY_RIGHT || input == 'd') p->x += s;

    if (input == ' ') {
        int bx = p->x + 3;
        int by = p->y - 1;
        bullet_spawn(bx, by);
    }
}

void player_draw(Player *p) {
    
    int cx = p->x;
    int cy = p->y;

    mvprintw(cy - 2, cx - 1, "O ");
    mvprintw(cy - 1, cx - 2, "/Y\\");
    mvprintw(cy + 0, cx - 3, "o/_\\o");
    mvprintw(cy + 1, cx - 1, "W ");
}
