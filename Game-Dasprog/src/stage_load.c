#include "../include/stage_load.h"
#include "../include/player.h"
#include "../include/enemybullet.h"

void stage_load(int stage, Player *p, Enemy *e) {
    p->hp = 20 + stage * 20;
    p->damage = 1 + stage * 2;
    p->speed = 1 + (stage * 0.5);

    e->hp = 40 + stage * 20;
    
    enemy_bullet_set_damage(1 + stage );


    background_init(stage);
}
