#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#define MAX_EBULLETS 200

typedef struct {
    int x, y;
    int dx, dy;     
    int active;
} EnemyBullet;

void enemy_bullet_init();
void enemy_bullet_spawn(int x, int y, int dx, int dy);
void enemy_bullet_update();
void enemy_bullet_draw();

void enemy_bullet_collision(struct Player *p);

#endif
