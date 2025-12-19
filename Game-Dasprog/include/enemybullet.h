#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#include "player.h"
#include "enemy.h"

#define MAX_EBULLETS 100

static int EBULLET_DAMAGE = 5;

typedef struct {
    int x, y;
    int dx, dy;     
    int active;
    int size;
    char sprite[5];
} EnemyBullet;

void enemy_bullet_init();
void enemy_bullet_spawn(int current, int x, int y, int dx, int dy);
void enemy_bullet_update();
void enemy_bullet_draw();
void enemy_bullet_collision(Player *p);
void enemy_bullet_pattern(int current, Enemy *e);


void enemy_bullet_set_damage(int dmg);

#endif
