#ifndef STAGE_H
#define STAGE_H

#include "player.h"

void stage_start(int stage_number, Player *p);
void stage_story(int stage);
void stage_storybegin(int stage);
void stage_upgrade(int stage, Player *p);
void stage_background(int stage);
void stage_endcredit(int stage);

#endif
