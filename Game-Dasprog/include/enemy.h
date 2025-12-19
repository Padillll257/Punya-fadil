#ifndef ENEMY_H
#define ENEMY_H
#include "player.h"
typedef struct {
    int x, y;      
    int hp;
    int move_timer;
    int radius;
    int phase;
    int dir;
    float angle;
    float orbit_r;
    int slow;
    int shadow_top_y;
    int shadow_bottom_y;
    int mouth_x;
    int mouth_y;

    int width;
    int height;
} Enemy;

void enemy_init(int current, Enemy *e);
void enemy_update(int current, Enemy *e, int player_x, int player_y, int player_damage);
void enemy_draw(int current, Enemy *e);

#endif


