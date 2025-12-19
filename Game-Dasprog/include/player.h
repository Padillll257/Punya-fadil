#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int x, y;
    int hp;
    int max_hp;

    int width;
    int height;

    int damage;
    int speed;
} Player;

void player_init(Player *p);
void player_update(Player *p, int input);
void player_draw(Player *p );

#endif
