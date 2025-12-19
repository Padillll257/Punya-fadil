#include <ncurses.h>
#include <string.h>

#include "../include/enemybullet.h"
#include "../include/player.h"
#include "../include/enemy.h"

EnemyBullet ebullets[MAX_EBULLETS];

void enemy_bullet_set_damage(int dmg) {
    EBULLET_DAMAGE += dmg;
}

void enemy_bullet_init() {
    for (int i = 0; i < MAX_EBULLETS; i++)
        ebullets[i].active = 0;
}

void enemy_bullet_spawn(int current, int x, int y, int dx, int dy) {
    for (int i = 0; i < MAX_EBULLETS; i++) {
        if (!ebullets[i].active) {
            EnemyBullet *b = &ebullets[i];

            b->active = 1;
            b->x = x;
            b->y = y;
            b->dx = dx;
            b->dy = dy;

            switch (current) {
                case 1:
                    strcpy(b->sprite, "o");
                    break;
                case 2:
                    strcpy(b->sprite, "<=>");
                    break;
                case 3:
                    strcpy(b->sprite, "@");
                    break;
            }
            break;
        }
    }
}

void enemy_bullet_pattern(int current, Enemy *e) {
    switch (current) {

    case 1: // 4 arah biasa
        enemy_bullet_spawn(1, e->x, e->y,  1,  0);
        enemy_bullet_spawn(1, e->x, e->y, -1,  0);
        enemy_bullet_spawn(1, e->x, e->y,  0,  1);
        enemy_bullet_spawn(1, e->x, e->y,  0, -1);

        enemy_bullet_spawn(1, e->x, e->y-2,  1,  0);
        enemy_bullet_spawn(1, e->x, e->y-2, -1,  0);
        enemy_bullet_spawn(1, e->x, e->y-2,  0,  1);
        enemy_bullet_spawn(1, e->x, e->y-2,  0, -1);
        break;

    case 2: // 4 arah + diagonal
        enemy_bullet_spawn(2, e->x, e->y,  1,  0);
        enemy_bullet_spawn(2, e->x, e->y, -1,  0);
        enemy_bullet_spawn(2, e->x, e->y,  0,  1);
        enemy_bullet_spawn(2, e->x, e->y,  0, -1);

        // diagonal
        enemy_bullet_spawn(2, e->x, e->y,  1,  1);
        enemy_bullet_spawn(2, e->x, e->y, -1, -1);
        enemy_bullet_spawn(2, e->x, e->y, -1,  1);
        enemy_bullet_spawn(2, e->x, e->y,  1, -1);

        enemy_bullet_spawn(2, e->x-40, e->shadow_bottom_y,  1,  0);
        enemy_bullet_spawn(2, e->x-40, e->shadow_bottom_y, -1,  0);
        enemy_bullet_spawn(2, e->x-40, e->shadow_bottom_y,  0,  1);
        enemy_bullet_spawn(2, e->x-40, e->shadow_bottom_y,  0, -1);

        // diagonal
        enemy_bullet_spawn(2, e->x-40, e->shadow_bottom_y,  1,  1);
        enemy_bullet_spawn(2, e->x-40, e->shadow_bottom_y, -1, -1);
        enemy_bullet_spawn(2, e->x-40, e->shadow_bottom_y, -1,  1);
        enemy_bullet_spawn(2, e->x-40, e->shadow_bottom_y,  1, -1);

        enemy_bullet_spawn(2, e->x-40, e->shadow_top_y,  1,  0);
        enemy_bullet_spawn(2, e->x-40, e->shadow_top_y, -1,  0);
        enemy_bullet_spawn(2, e->x-40, e->shadow_top_y,  0,  1);
        enemy_bullet_spawn(2, e->x-40, e->shadow_top_y,  0, -1);

        // diagonal
        enemy_bullet_spawn(2, e->x-40, e->shadow_top_y,  1,  1);
        enemy_bullet_spawn(2, e->x-40, e->shadow_top_y, -1, -1);
        enemy_bullet_spawn(2, e->x-40, e->shadow_top_y, -1,  1);
        enemy_bullet_spawn(2, e->x-40, e->shadow_top_y,  1, -1);
        break;

    case 3:
        enemy_bullet_spawn(3, e->x, e->y+2, -2, 0);
        enemy_bullet_spawn(3, e->x, e->y,   -2, 0);
        enemy_bullet_spawn(3, e->x, e->y-2, -2, 0);
        break;
    }
}

void enemy_bullet_update() {
    for (int i = 0; i < MAX_EBULLETS; i++) {
        if (ebullets[i].active) {
            ebullets[i].x += ebullets[i].dx;
            ebullets[i].y += ebullets[i].dy;

            if (ebullets[i].x < 1 || ebullets[i].x > COLS-1 ||
                ebullets[i].y < 1 || ebullets[i].y > LINES-1) {
                ebullets[i].active = 0;
            }
        }
    }
}

void enemy_bullet_draw() {
    for (int i = 0; i < MAX_EBULLETS; i++) {
        if (ebullets[i].active) {
            mvprintw(ebullets[i].y, ebullets[i].x, "%s", ebullets[i].sprite);
        }
    }
}

void enemy_bullet_collision(Player *p) {
    for (int i = 0; i < MAX_EBULLETS; i++) {
        if (ebullets[i].active &&
            ebullets[i].x == p->x &&
            ebullets[i].y == p->y) {

            ebullets[i].active = 0;
            p->hp -= EBULLET_DAMAGE;
        }
    }
}
