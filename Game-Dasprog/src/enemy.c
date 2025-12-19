#include <ncurses.h>
#include <stdlib.h>
#include <math.h>       
#include "enemy.h"
#include "enemybullet.h"
#include "bullet.h"
#include "../include/player.h"


void enemy_init(int current, Enemy *e) {
    e->hp = 80;
    e->radius = 15;
    e->move_timer = 0;

    e->phase = 0;
    e->dir   = 0;
    e->angle = 0;
    e->orbit_r = 40;
    e->slow = 0;

    e->x = COLS - COLS/4;
    e->y = 5;

    e->shadow_top_y = e->y +2;
    e->shadow_bottom_y = e->y + 40;
    int mouth_x = e->x + e->width/2;   
    int mouth_y = e->y - 5;            



    switch(current) {
    case 1:
        e->width  = 9;
        e->height = 5;
        break;

    case 2:
        e->width  = 13;
        e->height = 4;
        break;

    case 3:
        e->width  = 36;
        e->height = 15;
        break;
    }
}



void enemy_update(int current, Enemy *e, int px, int py, int player_damage){

    switch (current) {

    case 1 :

        e->move_timer++;


        if (e->move_timer % 10 == 0) {
            enemy_bullet_pattern(current, e);
        }

        if (e->move_timer % 5 == 0) { 
            int mid = COLS / 2;
            if(py > e->y) e->y++;
            else if(py < e->y) e->y--;

            if(rand() % 10 < 4) e->x+=(rand() % 2 == 0) ? 1 : -1;

            if(e->x < mid + 2) e->x = mid + 2;
            if(e->x > COLS - 2) e->x = COLS - 2;
        }

        if(bullet_check_and_clear(e->x,e->y)){
            e->hp -= player_damage;
        }

        break;

case 2:

    e->move_timer++;

    if (e->move_timer % 30 == 0) {
        enemy_bullet_pattern(current, e);
    }

    if (e->dir == 0) e->y--;
    else            e->y++;

    if (e->y < LINES/2 - 6) e->dir = 1;
    if (e->y > LINES/2 + 6) e->dir = 0;

    if (bullet_check_and_clear(e->x, e->y)) {
        e->hp -= player_damage;
    }

    break;

    case 3:

        e->move_timer++;


        if (e->move_timer % 10 == 0) {
            enemy_bullet_pattern(current, e);
        }

        if (e->move_timer % 5 == 0) { 
            int mid = COLS / 2;
            if(py > e->y) e->y++;
            else if(py < e->y) e->y--;

            if(rand() % 10 < 4) e->x+=(rand() % 2 == 0) ? 1 : -1;

            if(e->x < mid + 2) e->x = mid + 2;
            if(e->x > COLS - 2) e->x = COLS - 2;
        }

        if(bullet_check_and_clear(e->x,e->y)){
            e->hp -= player_damage;
        }

        break;

    }

    }



void enemy_draw(int current, Enemy *e) {
    switch (current)
    {
    case 1:
        if (e->hp <= 0) {
            mvprintw(e->y, e->x, "X");
            return;
        }

        {
        int sx = e->x - e->width / 2;
        int sy = e->y - e->height / 2;

        attron(COLOR_PAIR(2));

        mvprintw(sy + 0, sx, "  ._O_.   ");
        mvprintw(sy + 1, sx, " /_\\o/_\\  ");
        mvprintw(sy + 2, sx, "   /H\\    ");
        mvprintw(sy + 3, sx, "  (=O=).  ");
        mvprintw(sy + 4, sx, "    U.    ");

        attroff(COLOR_PAIR(2));
        }
        break;

case 2:

    if (e->hp <= 0) {
        mvprintw(e->y, e->x, "X");
        return;
    }

    attron(COLOR_PAIR(2));

    int sx = e->x - e->width / 2;

    mvprintw(e->shadow_top_y - 2, sx-40, "      |_|   ,");
    mvprintw(e->shadow_top_y - 1, sx-40, "     ('.') ///");
    mvprintw(e->shadow_top_y + 0, sx-40, "     <(_)`-/'");
    mvprintw(e->shadow_top_y + 1, sx-40, " <-._/J L /");

    mvprintw(e->shadow_bottom_y - 2, sx-40, "      |_|   ,");
    mvprintw(e->shadow_bottom_y - 1, sx-40, "     ('.') ///");
    mvprintw(e->shadow_bottom_y + 0, sx-40, "     <(_)`-/'");
    mvprintw(e->shadow_bottom_y + 1, sx-40, " <-._/J L /");

    int sy = e->y - e->height / 2;
    mvprintw(sy + 0, sx-40, "      |_|   ,");
    mvprintw(sy + 1, sx-40, "     ('.') ///");
    mvprintw(sy + 2, sx-40, "     <(_)`-/'");
    mvprintw(sy + 3, sx-40, " <-._/J L /");

    attroff(COLOR_PAIR(2));

    break;


    case 3:
        if (e->hp <= 0) {
            mvprintw(e->y, e->x, "X");
            return;
        }

        {
            int sx = e->x - e->width / 2;
            int sy = e->y - e->height / 2;

            attron(COLOR_PAIR(2));

            mvprintw(sy +  0, sx, "            <>=======()");
            mvprintw(sy +  1, sx, "           (/\\___   /|\\\\          ()==========<>_");
            mvprintw(sy +  2, sx, "                 \\_/ | \\\\        //|\\   ______/ \\)");
            mvprintw(sy +  3, sx, "                   \\_|  \\\\      // | \\_/");
            mvprintw(sy +  4, sx, "                     \\|\\/|\\_   //  /\\/");
            mvprintw(sy +  5, sx, "                      (oo)\\ \\_//  /");
            mvprintw(sy +  6, sx, "                     //_\\/\\_\\/ /  |");
            mvprintw(sy +  7, sx, "                    @@/  |=\\  \\  |");
            mvprintw(sy +  8, sx, "                         \\_=\\_ \\ |");
            mvprintw(sy +  9, sx, "                           \\==\\ \\|\\_ snd");
            mvprintw(sy + 10, sx, "                        __(\\===\\(  )\\");
            mvprintw(sy + 11, sx, "                       (((~) __(_/   |");
            mvprintw(sy + 12, sx, "                            (((~) \\  /");
            mvprintw(sy + 13, sx, "                            ______/ /");
            mvprintw(sy + 14, sx, "                            '------'");

            attroff(COLOR_PAIR(2));
        }
        break;

    }
}





