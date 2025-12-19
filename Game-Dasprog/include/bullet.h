#ifndef BULLET_H
#define BULLET_H

#define MAX_BULLETS 50

typedef struct {
    int x, y;
    int active;
} Bullet;

void bullet_init();
void bullet_spawn(int x, int y);
void bullet_update();
void bullet_draw();

int bullet_check_and_clear(int x, int y);

#endif
