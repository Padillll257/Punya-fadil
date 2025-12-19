#include <ncurses.h>
#include <unistd.h>

#include "../include/game.h"
#include "../include/player.h"
#include "../include/enemy.h"
#include "../include/stage.h"
#include "../include/bullet.h"
#include "../include/enemybullet.h"
#include "../include/background.h"
#include "../include/game_state.h"
#include "../include/audio.h"

Player player;
Enemy enemy;
EnemyBullet enemybullet;

GameState state = GAME_RUNNING;
int last_music_stage = -1;


void game_init() {
    bullet_init();
    enemy_bullet_init();
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    start_color();
    for(int i = 1; i <= 7; i++){
        init_pair(i, i, COLOR_BLACK);
    }

    player_init(&player);
    enemy_init(CURRENT_STAGE, &enemy);

    stage_load(CURRENT_STAGE, &player, &enemy);
    stage_start(CURRENT_STAGE, &player);

    state = GAME_RUNNING;
}


int pause_menu() {
    nodelay(stdscr, FALSE);

    const char* options[] = { "Resume", "Restart", "Exit to Menu" };
    int choice = 0;
    int total = 3;

    while (1) {
        clear();

        mvprintw(5, 10,  "  ================================");
        mvprintw(6, 10,  "       ||     GAME PAUSED     ||");
        mvprintw(7, 10,  "  ================================");

        for (int i = 0; i < total; i++) {
            if (i == choice)
                mvprintw(9 + i, 12, "> %s", options[i]);
            else
                mvprintw(9 + i, 12, "  %s", options[i]);
        }

        mvprintw(13, 12, "(Use ↑↓ arrow keys, Enter)");

        refresh();

        int ch = getch();

        if (ch == KEY_UP) {
            choice = (choice - 1 + total) % total;
        } else if (ch == KEY_DOWN) {
            choice = (choice + 1) % total;
        } else if (ch == '\n' || ch == KEY_ENTER) {
            return choice;   
        }
    }
}


void game_loop() {
    while (1) {

        clear();
        int ch = getch();
        if (ch == 'k') break;

        if (ch == 'p') {
            int res = pause_menu();

            if (res == 0) {
                nodelay(stdscr, TRUE);
            }
            else if (res == 1) {
                game_init(); 
                continue;
            }
            else if (res == 2) {
                state = GAME_LOSE;
                break;
            }
        }

        if (CURRENT_STAGE != last_music_stage) {
    if (CURRENT_STAGE == 1)
        play_music("assets/music/stage_1.ogg", -1);
    else if (CURRENT_STAGE == 2)
        play_music("assets/music/stage_2.ogg", -1);
    else if (CURRENT_STAGE == 3)
        play_music("assets/music/stage_3.ogg", -1);

    last_music_stage = CURRENT_STAGE;
}
 

        switch (CURRENT_STAGE) {

        case 1:
            background_update();
            background_draw(CURRENT_STAGE);

            if (ch == ' ' || ch == 'k') {
                bullet_spawn(player.x + 4, player.y - 2);
            }

            player_update(&player, ch);
            enemy_update(CURRENT_STAGE, &enemy, player.x, player.y, player.damage);

            bullet_update();
            enemy_bullet_update();
            enemy_bullet_collision(&player);

            player_draw(&player);
            enemy_draw(CURRENT_STAGE, &enemy);
            bullet_draw();
            enemy_bullet_draw();
            break;

        case 2:
            background_update();
            background_draw(CURRENT_STAGE);

            if (ch == ' ' || ch == 'k') {
                bullet_spawn(player.x + 4, player.y - 2);
            }

            player_update(&player, ch);
            enemy_update(CURRENT_STAGE, &enemy, player.x, player.y, player.damage);

            bullet_update();
            enemy_bullet_update();
            enemy_bullet_collision(&player);

            player_draw(&player);
            enemy_draw(CURRENT_STAGE, &enemy);
            bullet_draw();
            enemy_bullet_draw();
            break;


        case 3:

            background_update();
            background_draw(CURRENT_STAGE);

            if (ch == ' ' || ch == 'k') {
                bullet_spawn(player.x + 4, player.y - 2);
            }

            player_update(&player, ch);
            enemy_update(CURRENT_STAGE, &enemy, player.x, player.y, player.damage);

            bullet_update();
            enemy_bullet_update();
            enemy_bullet_collision(&player);

            player_draw(&player);
            enemy_draw(CURRENT_STAGE, &enemy);
            bullet_draw();
            enemy_bullet_draw();
            break;
        }

        if (enemy.hp <= 0 && state == GAME_RUNNING) {
            state = GAME_WIN;
        }
        if (player.hp <= 0 && state == GAME_RUNNING) {
            state = GAME_LOSE;
        }

        if (state == GAME_WIN || state == GAME_LOSE) {

            nodelay(stdscr, FALSE);

            int box_width = 34;
            int box_height = 9;
            int start_x = COLS/2 - box_width/2;
            int start_y = LINES/2 - box_height/2;

            mvprintw(start_y,     start_x, "+----------------------------------+");
            for (int i = 1; i < 8; i++)
                mvprintw(start_y + i, start_x, "|                                  |");
            mvprintw(start_y + 8, start_x, "+----------------------------------+");

            if (state == GAME_WIN) {
                mvprintw(start_y + 2, start_x + 12, "YOU WIN!");
                mvprintw(start_y + 3, start_x + 6,  "Stage Cleared — Nice!");

                if (CURRENT_STAGE < 3) {
                    mvprintw(start_y + 5, start_x + 7, "Press any key to continue");
                } else {
                    mvprintw(start_y + 5, start_x + 6, "You cleared all stages!");
                }

            } else {
                mvprintw(start_y + 2, start_x + 12, "GAME OVER");
                mvprintw(start_y + 3, start_x + 6,  "Your journey ends here");
                mvprintw(start_y + 5, start_x + 8,  "Press any key to exit");
            }

            refresh();
            getch();

            if (state == GAME_WIN) {
                if (CURRENT_STAGE < 3) {   
                    next_stage();       
                    game_init();        
                    continue;
                } 
                else {
                    clear();
                    stage_endcredit(CURRENT_STAGE);
                    getch();
                    break;
                }
            }

            break;
        }

        mvprintw(0, 2, "HP: %d  EnemyHP: %d  Stage: %d  Dmg: %d  Spd: %d",
                 player.hp, enemy.hp, CURRENT_STAGE, player.damage, player.speed);

        refresh();
        usleep(30000);
    }
}


void game_end() {
    endwin();
}
