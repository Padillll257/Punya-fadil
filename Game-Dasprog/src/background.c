#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/background.h"
#include "../include/stage_load.h"

static int offsetC = 0;   
static int offset0 = 0;   
static int offset1 = 0;  
static int offset2 = 0;  

static const char *layer_cloud[] = {
    "      ___----___       ___---___      ",
    "  __--         --__ __-         -__   ",
};
static int cloud_lines = 2;

static const char *layer0[] = {
    " .    .    .   .   .    . ",
    "   .      .       .    .  ",
    " .   .     .   .        . ",
};
static int layer0_lines = 3;

static const char *layer1[] = {
    "   &&&        &&&&       &&&      &&&&   ",
    "  &&&&&      &&&&&      &&&&&     &&&&&  ",
    "    ||         ||         ||        ||   ",
};
static int layer1_lines = 3;

static const char *layer2[] = {
    "  /--\\       /--\\       /--\\        o ",
    "  |  |        |  |        |  |        /|\\",
    "  |__|        |__|        |__|        / \\",
};
static int layer2_lines = 3;


static const char *s2_top[] = {
    "============================================================",
};
static int s2_top_lines = 1;

static const char *s2_bottom[] = {
    "============================================================",
};
static int s2_bottom_lines = 1;

static const char *s2_stalactite[] = {
    "   v     v      v   v      v     v   ",
    "  v v   v v    v v v v    v v   v v  ",
};
static int s2_stalactite_lines = 2;

static const char *s2_stalagmite[] = {
    "  ^   ^      ^      ^   ^    ^    ",
    " ^ ^ ^ ^    ^ ^    ^ ^ ^ ^  ^ ^   ",
};
static int s2_stalagmite_lines = 2;

static const char *s2_sidewall[] = {
    "||",
    "||",
    "||",
    "||",
    "||",
};
static int s2_sidewall_lines = 5;

static const char *s2_window[] = {
    "   []     []     []",
    "   ||     ||     ||",
    "   []     []     []",
};
static int s2_window_lines = 3;

static const char *s2_fire1[] = {
    "  (  )   ( )  (   )  ( )   (  )",
    "   )(__ )(__  )(__  )(__  )(__ )",
};
static const char *s2_fire2[] = {
    " ( )   (   )   ( )   (   )   ( ) ",
    "(__ )  )(__   (__ )  )(__   (__ )",
};
static int s2_fire_lines = 2;

static const char *s3_castle_left[] = {
"                                       ,.=,,==. ,,_",
"                      _ ,====, _    |I|`` ||  `|I `|",
"                     |`I|    || `==,|``   ^^   ``  |",
"                     | ``    ^^    ||_,===TT`==,,_ |",
"                     |,==Y``Y==,,__| \\L=_-`'   +J/`",
"                      \\|=_  ' -=#J/..-|=_-     =|",
"                       |=_   -;-='`. .|=_-     =|----T--,",
"                       |=/\\  -|=_-. . |=_-/^\\  =||-|-|::|____",
"                       |=||  -|=_-. . |=_-| |  =|-|-||::\\____",
"                       |=LJ  -|=_-. . |=_-|_| =||-|-|:::::::",
"                       |=_   -|=_-_.  |=_-     =|-|-||:::::::",
"                       |=_   -|=//^. |=_-      =||-|-|:::::::",
"                   ,   |/&_,_-|=||  | |=_-     =|-|-||:::::::",
"                ,--``8%,/    ',%||  | |=_-     =||-|-|%::::::",
"            ,---`_,888`  ,.'''''`-.,|,|/!,--,.&\\|&\\-,|&#:::::",
"           |;:;K`__,...;=\\_____,=``           %%%&     %#,---",
"           |;::::::::::::|       `'.________+-------\\   ``",
"          /8M%;:::;;:::::|                  |        `-------",
};
static int s3_castle_left_lines = 18;


static const char *s3_left_castle2[] = {
"     |Zz.                      |Zz.",
"     |                         |",
"    _L__                      _|",
"   (____)      _             /__\\",
"   /____\\     /_\\           /____\\",
"  (______)    | |          (______)",
"   |  U |_____| |___________| U  |",
"   |u   | |  |   __   |  |  |   u|",
"   |    | |  |  ||||  |  |  |    |",
"   -------------\"\"\"\"--------------js",
};
static int s3_left_castle2_lines = 10;



static const char *s3_middle[] = {
"               /\\",
"          /\\  //\\\\",
"   /\\    //\\\\///\\\\\\",
"  //\\\\  ///\\////\\\\\\\\  /\\",
"/  ^ \\/^ ^/^  ^  ^ \\/^ \\/  ^ \\",
};
static int s3_middle_lines = 5;

static const char *s3_big_cloud[] = {
"            ________      _________       ________",
"      ___--          ---__           ----        ---__",
" __--                    ---___                     --__",
};
static int s3_big_cloud_lines = 3;


static const char *s3_big_lightning1[] = {
"       \\",
"        \\\\",
"         \\\\\\",
"          \\\\\\\\\\",
};
static const char *s3_big_lightning2[] = {
"        |",
"       /",
"      //",
"     ///",
};
static int s3_big_lightning_lines = 4;

static void safe_draw(int y, int x, const char *str) {
    if (y < 0 || y >= LINES) return;

    int len = strlen(str);
    int start = 0;

    if (x < 0) {
        start = -x;
        x = 0;
    }

    if (x >= COLS) return; 

    int max_draw = COLS - x;
    if (max_draw <= 0) return;

    mvprintw(y, x, "%.*s", max_draw, str + start);
}



static void draw_layer(const char **layer, int lines, int start_y, int offset) {
    for (int i = 0; i < lines; i++) {
        int len = strlen(layer[i]);
        int raw_x = COLS - (offset % len);

        int y = start_y + i;
        if (y < 0 || y >= LINES) continue;

        safe_draw(y, raw_x, layer[i]);
        safe_draw(y, raw_x - len, layer[i]);
    }
}



void background_init(int current_stage) {
    offsetC = offset0 = offset1 = offset2 = 0;
}

void background_update() {
    offsetC = (offsetC + 1) % 400;
    offset0 = (offset0 + 1) % 300;
    offset1 = (offset1 + 1) % 300;
    offset2 = (offset2 + 2) % 300;
}

static int get_max_width(const char **arr, int lines) {
    int maxw = 0;
    for (int i = 0; i < lines; i++) {
        int w = strlen(arr[i]);
        if (w > maxw) maxw = w;
    }
    return maxw;
}



void background_draw(int current_stage) {

    switch (current_stage) {

        case 1:   // ORIGINAL STAGE (SKY + TREES)
            draw_layer(layer_cloud, cloud_lines, 2, offsetC);
            draw_layer(layer0, layer0_lines, LINES - 12, offset0);
            draw_layer(layer1, layer1_lines, LINES - 9, offset1);
            draw_layer(layer2, layer2_lines, LINES - 6, offset2);
            break;

        case 2:   // DEVIL CAVE

            draw_layer(s2_top, s2_top_lines, 1, offset0);

            draw_layer(s2_stalactite, s2_stalactite_lines, 2, offset1);

            draw_layer(s2_window, s2_window_lines, LINES/2 - 3, offset0);

            draw_layer(s2_bottom, s2_bottom_lines, LINES - 3, offset0);

            draw_layer(s2_stalagmite, s2_stalagmite_lines, LINES - 6, offset1);

            for(int i=0;i<s2_sidewall_lines;i++)
                mvprintw(5+i, 1, "%s", s2_sidewall[i]);

            for(int i=0;i<s2_sidewall_lines;i++)
                mvprintw(5+i, COLS-3, "%s", s2_sidewall[i]);
            if((offsetC/10) % 2 == 0)
                draw_layer(s2_fire1, s2_fire_lines, LINES - 4, offset2);
            else
                draw_layer(s2_fire2, s2_fire_lines, LINES - 4, offset2);

            break;

    case 3:
    draw_layer(s3_big_cloud, s3_big_cloud_lines, 1, offsetC);

    if (rand() % 12 == 0)
        draw_layer(s3_big_lightning1, s3_big_lightning_lines, 3, offset2);
    else if (rand() % 12 == 1)
        draw_layer(s3_big_lightning2, s3_big_lightning_lines, 3, offset2);

    {
        int mid_x = (COLS - get_max_width(s3_middle, s3_middle_lines)) / 2;
        int base_y = LINES - s3_middle_lines - 1;

        for (int i = 0; i < s3_middle_lines; i++) {
            safe_draw(base_y + i, mid_x, s3_middle[i]);
        }
    }

    {
        int w = get_max_width(s3_castle_left, s3_castle_left_lines);
        int base_y = LINES - s3_castle_left_lines - 1;
        int x = COLS - w - 2;

        for (int i = 0; i < s3_castle_left_lines; i++) {
            safe_draw(base_y + i, x, s3_castle_left[i]);
        }
    }

    {
        int base_y = LINES - s3_left_castle2_lines - 1;
        int x = 2;  

        for (int i = 0; i < s3_left_castle2_lines; i++) {
            safe_draw(base_y + i, x, s3_left_castle2[i]);
        }
    }

    break;

    }
}
