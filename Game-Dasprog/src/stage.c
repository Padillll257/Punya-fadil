#include <ncurses.h>
#include "../include/stage.h"
#include "../include/player.h"
#include "../include/game_state.h"
#include "../include/audio.h"

void print_slow(int y, int x, const char *text, int delay_ms) {
    for (int i = 0; text[i] != '\0'; i++) {
        mvaddch(y, x + i, text[i]);
        refresh();
        napms(delay_ms);
    }
}

void draw_box(int y, int x, int w, int h) {
    mvprintw(y, x, "+");
    mvprintw(y, x + w - 1, "+");
    mvprintw(y + h - 1, x, "+");
    mvprintw(y + h - 1, x + w - 1, "+");

    for (int i = 1; i < w - 1; i++) {
        mvprintw(y, x + i, "-");
        mvprintw(y + h - 1, x + i, "-");
    }

    for (int i = 1; i < h - 1; i++) {
        mvprintw(y + i, x, "|");
        mvprintw(y + i, x + w - 1, "|");
    }
}

const char *ascii_small[] = {
    "     /\_/\     SYSTEM BOOT READY",
    "    ( o.o )    AI: HERTA-UNIT-01 ONLINE",
    "     > ^ <"
};

void stage_menu(int stage) {

    play_music("assets/music/menu.ogg" , -1);
    clear();
    start_color();

    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);  
    init_pair(2, COLOR_CYAN, COLOR_BLACK);     
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);   
    init_pair(4, COLOR_GREEN, COLOR_BLACK);    
    init_pair(5, COLOR_RED, COLOR_BLACK);      

    int midX = COLS / 2;

    const char *title1 = "=== THE JOURNEY OF ===";
    const char *title2 = "=== HERTA THE WITCH ===";

    attron(COLOR_PAIR(1));
    mvprintw(2, midX - (strlen(title1) / 2), "%s", title1);
    mvprintw(3, midX - (strlen(title2) / 2), "%s", title2);
    attroff(COLOR_PAIR(1));
const char *ascii[] = {
"                                        %                                            ",
"                                      %%%%                                           ",
"                                    %%%%#                                            ",
"                                   %%%%%#                                            ",
"                                  #%%%#+=                                            ",
"                                 %%%*%#%%#                                           ",
"                                %%#*+*%%%%#                                          ",
"                                #*#-#**#%#%#            @%@%%%%%@@                  ",
"                                #*++**##*++*##      @@%*+++++++++#                  ",
"                                ***==+++*##****%%%#+========+++*#                   ",
"                               =#*+-===+**%%%%%*=====---==+++*#%                    ",
"                              =+*====+*#%%%%*+======--==+++*#%                      ",
"                             ==+**#*#%%%#+=-----====+++++*#                         ",
"                            +*###%%%#*+=--:------=++++**                           ",
"                           ######*+=-=-------=-=-==                                 ",
"                       %%%%#*++==+=--=--====++=+==+                                 ",
"                   #%%%#**++++++++=+====::::-==**==                                 ",
"                @###*****#####%#**+*==-......-=**=+++                               ",
"                              ##++*=++=:....:=++**=+#                               ",
"                                +**==**+-::-+**++++=                                 ",
"                               +**++=+*##+++***=+=+++                                ",
"                              *##+++=++**++#*+*++-= #*                               ",
"                              # *==+=+-::::-:-:=+--:                                  ",
"                               :::.-==::-==-::.:+-..:                                 ",
"                               :...-+=-::==::--:-:...-                                ",
"                            --=:..:+*#*+=--=+*#*=:..:---                             ",
"                            *=-:::+%##+=+*++++###-::::-+*                            ",
"                            -==--:#%%@%######%@%%+::====%                            ",
"                           %#*==-=##%@@@#*##%@@%#*=-+=*%#                            ",
"                           %%#**#*###%##%%%%###***%@#+*%%                            ",
"                           @#***+**##*#%%##%%#*##***+#*##                            ",
"                           %#*###*##%##%%%%%#####***%#*#%                            ",
"                          %%%%@%#*#%#%%%%%%%#%##%%#+%%%%%%@                          ",
"                         %%%%%%%#*+*%%*=*+=*=*%%#+*#%%%%##%%                         ",
"                       #**++#%%+++*-=##=-::-=*#+-++++%%%+=+*#%                       ",
"                    @%%*+++#%%#**%%##**--:=*##**#%%++#%%#++**%%@                     ",
"                 %%%#++=+#%%%%%%%%%%+##+*##*=:-+#%%%%#%%%%*===+#%%                   ",
"                %#*+-:::=#%%%#%%%%%*+=#%%*-::::=#%%%%#%%%%*-:::-**##                 ",
"               %##=--:::=#%%%%%%%**===*+-::::::=+#%%%%%%%%*:::---+##                 ",
"               #+-::::::+#%%%%###*+=---:::::::::++=#%%%%@%+-::::::=*                 ",
"               *=--::::-+%%%*+===--:::::::::::::-=+++*#%%%*-:::::-=+*                ",
"               **++=--::=%%%#=----::::::::::::::::----=#%%+::::-+***                 ",
"                #*+-:-==#%%%%%+=-::::-::::::--:::-:==*%%%%#+==-:=***                 ",
"                *=:::-*#%%%%%%#=-:::-=--------::::-=*%%%%%%#**-:::-                  ",
"                :::--*#%%%#***+----=++**+==++=------+**#%%%%#*+-:::-                 ",
"                :-+-+###**+=+===++====++===++++==++=-=++*#%%%##+---:                 ",
"                :=-***+=----=++=======++===++++=+*#%%*+-==+*###*=--:                 ",
"                :--+==------++========++===+%%#**#%%%#+-----=+*#+==+                 ",
"                   ++===---=**=========+===+#%#***###**----===*##  %                 ",
};
    int ascii_x = 2;
    int ascii_y = 6;

    attron(COLOR_PAIR(4));
    int ascii_lines = sizeof(ascii) / sizeof(ascii[0]);
    for (int i = 0; i < ascii_lines; i++)
        mvprintw(ascii_y + i, ascii_x, "%s", ascii[i]);
    attroff(COLOR_PAIR(4));

    int box_w = 50;
    int box_h = 22;
    int box_x = midX + 18;
    int box_y = 5;

    attron(COLOR_PAIR(3));
    draw_box(box_y, box_x, box_w, box_h);
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(3));
    mvprintw(box_y + 1, box_x + (box_w / 2 - 6), "=== MENU ===");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(5));
    int sm_y = box_y + 3;
    int sm_x = box_x + 5;

    int small_lines = sizeof(ascii_small) / sizeof(ascii_small[0]);
    for (int i = 0; i < small_lines; i++) {
        mvprintw(sm_y + i, sm_x, "%s", ascii_small[i]);
    }
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(2));
    print_slow(box_y + 10, box_x + 3, "--Start Game--  (Press Space)", 15);
    mvprintw(box_y + 12, box_x + 3, "--Exit-- (Press Q)");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3));
    mvprintw(box_y + 14, box_x + 3, "Be Prepare");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(2));
    mvprintw(box_y + 16, box_x + 5, "For Thrilling");
    mvprintw(box_y + 17, box_x + 5, "Exciting");
    mvprintw(box_y + 18, box_x + 5, "And Mesmerizing Journey");
    attroff(COLOR_PAIR(2));

    refresh();

    while (1) {
        int c = getch();

        if (c == ' ' || c == '\n'){
            stop_music();
            break;
        }

        if (c == 'q' || c == 'Q') {
            audio_quit();
            endwin();
            exit(0);
        } 

    }
}

void stage_background(int stage) {
    for (int i = 0; i < COLS; i++) {
        attron(COLOR_PAIR(stage % 7 + 1));
        mvprintw(0, i, "=");
        attroff(COLOR_PAIR(stage % 7 + 1));
    }
}  


void print_story_slow(int y, int x, const char *text, int delay_ms) {
    for (int i = 0; text[i] != '\0'; i++) {
        mvaddch(y, x + i, text[i]);
        refresh();
        napms(delay_ms);
    }
}

void clear_story_box() {
    for (int i = 3; i < LINES - 3; i++) {
        for (int j = 2; j < COLS - 2; j++) {
            mvaddch(i, j, ' ');
        }
    }
}

void stage_storybegin(int stage) {
    play_music("assets/music/story_1.ogg" , -1);
    clear();
    start_color();

    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    attron(COLOR_PAIR(3));
    draw_box(1, 1, COLS - 2, LINES - 2);
    attroff(COLOR_PAIR(3));

    const char *chapter = "✦✦✦  CHAPTER 1 : THE LOST SORCERESS  ✦✦✦";
    int tx = COLS / 2 - strlen(chapter) / 2;

    attron(COLOR_PAIR(1));
    mvprintw(2, tx, "%s", chapter);
    attroff(COLOR_PAIR(1));

    const char *story_lines[] = {
        "Di sebuah kerajaan antah berantah berdirilah Kerajaan Astrava—",
        "negeri megah yang dipimpin oleh Raja Aventurine yang bijaksana.",
        "Di kerajaan itu hidup penyihir muda bernama Herta Sang Hebat,",
        "penyihir tempur utama dengan sihir yang sangat ditakuti.",
        "Sahabat terdekatnya, Topaz, adalah penyihir penelitian dan riset,",
        "selalu menemani Herta dalam berbagai eksperimen sihir mereka.",
        "Namun pada suatu malam yang gelap, kelompok penjahat misterius",
        "menyerang Astrava dan menculik Topaz tanpa meninggalkan jejak.",
        "Herta pun bersumpah menyelamatkan sahabatnya apa pun risikonya.",
        "Namun sebelum perjalanannya dimulai... sesosok musuh menghadangnya."
    };

    int total_lines = sizeof(story_lines) / sizeof(story_lines[0]);

    clear_story_box();   

    int cur_y = 6;

    for (int idx = 0; idx < total_lines; idx++) {

        attron(COLOR_PAIR(2));
        print_story_slow(cur_y, 6, story_lines[idx], 15);
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(4));
        mvprintw(LINES - 4, COLS - 28, "[ Tekan SPACE untuk lanjut ]");
        attroff(COLOR_PAIR(4));

        refresh();

        int c;
        while (1) {
            c = getch();
            if (c == ' ' || c == '\n'){
                break;
            }
        }

        cur_y += 2; 
    }

    attron(COLOR_PAIR(1));
    mvprintw(LINES / 2, COLS / 2 - 10, "✦ Petualangan dimulai... ✦");
    attroff(COLOR_PAIR(1));

    stop_music();

    refresh();
    napms(1200);
}


void stage_storybegin2(int stage) {
    play_music("assets/music/story_1.ogg" , -1);
    clear();
    start_color();

    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    attron(COLOR_PAIR(3));
    draw_box(1, 1, COLS - 2, LINES - 2);
    attroff(COLOR_PAIR(3));

    const char *chapter = "✦✦✦  CHAPTER 2 : THE DEVIL'S CAVERN  ✦✦✦";
    int tx = COLS / 2 - strlen(chapter) / 2;

    attron(COLOR_PAIR(1));
    mvprintw(2, tx, "%s", chapter);
    attroff(COLOR_PAIR(1));

    const char *story_lines[] = {
        "Herta berhasil mengalahkan musuh pertamanya, sang penjaga bayangan.",
        "Dengan luka di tubuhnya, penjaga itu mengungkapkan sebuah rahasia—",
        "\"Temanmu... Topaz... dibawa ke Istana Naga di utara...\"",
        "Namun untuk memasuki istana itu, seseorang membutuhkan sebuah kunci.",
        "Kunci Abyssal, artefak kuno yang tersembunyi di dalam Gua Iblis.",
        "Di dalam gua tersebut, hidup sang Devil yang dapat membagi dirinya menjadi tiga.",
        "Konon, hanya penyihir hebat yang mampu melawan ketiganya sekaligus.",
        "Tanpa berpikir panjang, Herta berangkat menuju Gua Devil tersebut.",
        "Udara gelap menyelimuti jalur masuk... langkahnya mulai berat.",
        "Dan dari kedalaman... suara tawa mengerikan menyambut kedatangannya."
    };

    int total_lines = sizeof(story_lines) / sizeof(story_lines[0]);

    clear_story_box();
    int cur_y = 6;

    for (int idx = 0; idx < total_lines; idx++) {

        attron(COLOR_PAIR(2));
        print_story_slow(cur_y, 6, story_lines[idx], 15);
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(4));
        mvprintw(LINES - 4, COLS - 28, "[ Tekan SPACE untuk lanjut ]");
        attroff(COLOR_PAIR(4));

        refresh();

        int c;
        while (1) {
            c = getch();
            if (c == ' ' || c == '\n') break;
        }

        cur_y += 2;
    }

    attron(COLOR_PAIR(1));
    mvprintw(LINES / 2, COLS / 2 - 12, "✦ Pertempuran pun dimulai... ✦");
    attroff(COLOR_PAIR(1));

    stop_music();

    refresh();
    napms(1200);
}

void stage_storybegin3(int stage) {
    play_music("assets/music/story_1.ogg" , -1);
    clear();
    start_color();

    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    attron(COLOR_PAIR(3));
    draw_box(1, 1, COLS - 2, LINES - 2);
    attroff(COLOR_PAIR(3));

    const char *chapter = "✦✦✦  CHAPTER 3 : THE DRAGON'S THRONE  ✦✦✦";
    int tx = COLS / 2 - strlen(chapter) / 2;

    attron(COLOR_PAIR(1));
    mvprintw(2, tx, "%s", chapter);
    attroff(COLOR_PAIR(1));

    const char *story_lines[] = {
        "Setelah pertarungan sengit, Herta berhasil memperoleh Kunci Abyssal.",
        "Ia pun melanjutkan perjalanannya menuju Istana Naga di puncak utara.",
        "Istana itu kuno dan tertutup kabut magis yang tak tersentuh waktu.",
        "Di tengah aula megah, Herta menemukan Topaz terkurung dalam kristal es.",
        "Namun ketika ia hendak mendekat, tanah bergetar hebat...",
        "Sesosok naga raksasa bangkit dari tidur panjangnya selama ratusan tahun.",
        "Sisiknya berkilau keemasan, dan matanya memancarkan kekuatan purba.",
        "\"Siapa yang berani mengusik singgasanaku?\" raung sang naga.",
        "Herta tahu, hanya satu pilihan: ia harus mengalahkan naga itu.",
        "Demi menyelamatkan sahabatnya, ia menyiapkan seluruh kekuatan magisnya."
    };

    int total_lines = sizeof(story_lines) / sizeof(story_lines[0]);

    clear_story_box();
    int cur_y = 6;

    for (int idx = 0; idx < total_lines; idx++) {

        attron(COLOR_PAIR(2));
        print_story_slow(cur_y, 6, story_lines[idx], 15);
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(4));
        mvprintw(LINES - 4, COLS - 28, "[ Tekan SPACE untuk lanjut ]");
        attroff(COLOR_PAIR(4));

        refresh();

        int c;
        while (1) {
            c = getch();
            if (c == ' ' || c == '\n') break;
        }

        cur_y += 2;
    }

    attron(COLOR_PAIR(1));
    mvprintw(LINES / 2, COLS / 2 - 14, "✦ Pertarungan terakhir dimulai! ✦");
    attroff(COLOR_PAIR(1));

    stop_music();

    refresh();
    napms(1200);
}


void stage_upgrade(int stage, Player *p) {
    play_music("assets/music/upgrade.ogg" , -1);
    clear();
    start_color();

    init_pair(1, COLOR_CYAN,   COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    int cx = COLS / 2;
    int cy = LINES / 2;

    const char *mascot[] = {
        "      /\\_/\\      ",
        "     ( o.o )     ",
        "      > ^ <      ",
        "  HERTA UNIT-01  ",
    };
    int masc_lines = sizeof(mascot) / sizeof(mascot[0]);

    attron(COLOR_PAIR(3));
    for (int i = 0; i < masc_lines; i++) {
        mvprintw(cy - 8 + i, cx - 35, "%s", mascot[i]);
    }
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1));
    mvprintw(cy - 7, cx - 10, "=== UPGRADE STAGE %d ===", stage);
    attroff(COLOR_PAIR(1));

    int box_w = 46;
    int box_h = 13;
    int box_x = cx - (box_w / 2);
    int box_y = cy - 6;

    // Draw box
    attron(COLOR_PAIR(4));
    mvprintw(box_y, box_x, "+");
    mvprintw(box_y, box_x + box_w - 1, "+");
    mvprintw(box_y + box_h - 1, box_x, "+");
    mvprintw(box_y + box_h - 1, box_x + box_w - 1, "+");

    for (int i = 1; i < box_w - 1; i++) {
        mvprintw(box_y, box_x + i, "-");
        mvprintw(box_y + box_h - 1, box_x + i, "-");
    }
    for (int i = 1; i < box_h - 1; i++) {
        mvprintw(box_y + i, box_x, "|");
        mvprintw(box_y + i, box_x + box_w - 1, "|");
    }
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(2));

    mvprintw(box_y + 2, box_x + 4, "[1]   (==)>  DAMAGE UP");
    mvprintw(box_y + 3, box_x + 7, "Increases your attack power (+1)");

    mvprintw(box_y + 5, box_x + 4, "[2]   [@]    SPEED UP");
    mvprintw(box_y + 6, box_x + 7, "Move faster between attacks (+1)");

    mvprintw(box_y + 8, box_x + 4, "[3]   <3     MAX HEALTH");
    mvprintw(box_y + 9, box_x + 7, "Increase your vitality (+5)");

    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(box_y + box_h + 1, cx - 15, "Tekan [1] [2] [3] untuk memilih");
    attroff(COLOR_PAIR(1));

    refresh();

    while (1) {
        int c = getch();
        if (c == '1') { p->damage++; stop_music(); break; }
        if (c == '2') { p->speed++;  stop_music(); break;}
        if (c == '3') { p->max_hp += 5; p->hp += 5; stop_music(); break; }
    }   

}

void stage_upgrade2(int stage, Player *p) {
    play_music("assets/music/upgrade.ogg" , -1);
    clear();
    start_color();

    init_pair(1, COLOR_CYAN,   COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    int cx = COLS / 2;
    int cy = LINES / 2;

    const char *mascot[] = {
        "      /\\_/\\      ",
        "     ( o.o )     ",
        "      > ^ <      ",
        "  HERTA UNIT-01  ",
    };
    int masc_lines = sizeof(mascot) / sizeof(mascot[0]);

    attron(COLOR_PAIR(3));
    for (int i = 0; i < masc_lines; i++) {
        mvprintw(cy - 8 + i, cx - 35, "%s", mascot[i]);
    }
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1));
    mvprintw(cy - 7, cx - 10, "=== UPGRADE STAGE %d ===", stage);
    attroff(COLOR_PAIR(1));

    int box_w = 46;
    int box_h = 13;
    int box_x = cx - (box_w / 2);
    int box_y = cy - 6;

    // Draw box
    attron(COLOR_PAIR(4));
    mvprintw(box_y, box_x, "+");
    mvprintw(box_y, box_x + box_w - 1, "+");
    mvprintw(box_y + box_h - 1, box_x, "+");
    mvprintw(box_y + box_h - 1, box_x + box_w - 1, "+");

    for (int i = 1; i < box_w - 1; i++) {
        mvprintw(box_y, box_x + i, "-");
        mvprintw(box_y + box_h - 1, box_x + i, "-");
    }
    for (int i = 1; i < box_h - 1; i++) {
        mvprintw(box_y + i, box_x, "|");
        mvprintw(box_y + i, box_x + box_w - 1, "|");
    }
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(2));

    mvprintw(box_y + 2, box_x + 4, "[1]   (==)>  DAMAGE UP");
    mvprintw(box_y + 3, box_x + 7, "Increases your attack power (+3)");

    mvprintw(box_y + 5, box_x + 4, "[2]   [@]    SPEED UP");
    mvprintw(box_y + 6, box_x + 7, "Move faster between attacks (+3)");

    mvprintw(box_y + 8, box_x + 4, "[3]   <3     MAX HEALTH");
    mvprintw(box_y + 9, box_x + 7, "Increase your vitality (+7)");

    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(box_y + box_h + 1, cx - 15, "Tekan [1] [2] [3] untuk memilih");
    attroff(COLOR_PAIR(1));

    refresh();

    while (1) {
        int c = getch();
        if (c == '1') { p->damage+= 3; stop_music(); break; }
        if (c == '2') { p->speed+= 3; stop_music(); break; }
        if (c == '3') { p->max_hp += 7; p->hp += 7;stop_music(); break; }
    }   

}

void stage_upgrade3(int stage, Player *p) {
    play_music("assets/music/upgrade.ogg" , -1);
    
    clear();
    start_color();

    init_pair(1, COLOR_CYAN,   COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    int cx = COLS / 2;
    int cy = LINES / 2;

    const char *mascot[] = {
        "      /\\_/\\      ",
        "     ( o.o )     ",
        "      > ^ <      ",
        "  HERTA UNIT-01  ",
    };
    int masc_lines = sizeof(mascot) / sizeof(mascot[0]);

    attron(COLOR_PAIR(3));
    for (int i = 0; i < masc_lines; i++) {
        mvprintw(cy - 8 + i, cx - 35, "%s", mascot[i]);
    }
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1));
    mvprintw(cy - 7, cx - 10, "=== UPGRADE STAGE %d ===", stage);
    attroff(COLOR_PAIR(1));

    int box_w = 46;
    int box_h = 13;
    int box_x = cx - (box_w / 2);
    int box_y = cy - 6;

    // Draw box
    attron(COLOR_PAIR(4));
    mvprintw(box_y, box_x, "+");
    mvprintw(box_y, box_x + box_w - 1, "+");
    mvprintw(box_y + box_h - 1, box_x, "+");
    mvprintw(box_y + box_h - 1, box_x + box_w - 1, "+");

    for (int i = 1; i < box_w - 1; i++) {
        mvprintw(box_y, box_x + i, "-");
        mvprintw(box_y + box_h - 1, box_x + i, "-");
    }
    for (int i = 1; i < box_h - 1; i++) {
        mvprintw(box_y + i, box_x, "|");
        mvprintw(box_y + i, box_x + box_w - 1, "|");
    }
    attroff(COLOR_PAIR(4));

    attron(COLOR_PAIR(2));

    mvprintw(box_y + 2, box_x + 4, "[1]   (==)>  DAMAGE UP");
    mvprintw(box_y + 3, box_x + 7, "Increases your attack power (+8)");

    mvprintw(box_y + 5, box_x + 4, "[2]   [@]    SPEED UP");
    mvprintw(box_y + 6, box_x + 7, "Move faster between attacks (+5)");

    mvprintw(box_y + 8, box_x + 4, "[3]   <3     MAX HEALTH");
    mvprintw(box_y + 9, box_x + 7, "Increase your vitality (+12)");

    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    mvprintw(box_y + box_h + 1, cx - 15, "Tekan [1] [2] [3] untuk memilih");
    attroff(COLOR_PAIR(1));

    refresh();

    while (1) {
        int c = getch();
        if (c == '1') { p->damage+= 8; stop_music(); break; }
        if (c == '2') { p->speed+= 5;  stop_music(); break; }
        if (c == '3') { p->max_hp += 12; p->hp += 12; stop_music(); break; }
    }   

}

void stage_endcredit(int stage) {
    clear();
    start_color();

    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    attron(COLOR_PAIR(3));
    draw_box(1, 1, COLS - 2, LINES - 2);
    attroff(COLOR_PAIR(3));

    const char *chapter = "✦✦✦  FINAL CHAPTER : RETURN OF THE HERO  ✦✦✦";
    int tx = COLS / 2 - strlen(chapter) / 2;

    attron(COLOR_PAIR(1));
    mvprintw(2, tx, "%s", chapter);
    attroff(COLOR_PAIR(1));

    const char *story_lines[] = {
        "Setelah pertempuran yang mengguncang istana, naga purba itu tumbang.",
        "Cahaya hangat memancar dari kristal es yang retak perlahan.",
        "Topaz akhirnya bebas—dengan senyum lega dan mata yang berkaca-kaca.",
        "\"Herta... kau datang untukku.\"",
        "Mereka berdua pun meninggalkan Istana Naga dengan langkah tenang.",
        "",
        "Kabut puncak utara terbuka, menyingkap jalan pulang menuju kerajaan.",
        "Penduduk menyambut mereka dengan sorak bahagia penuh haru.",
        "Sang raja memberi penghormatan: \"Kerajaan berhutang nyawa padamu, Herta.\"",
        "",
        "Setelah sekian panjang perjalanan, persahabatan mereka terjalin semakin kuat.",
        "Mereka hidup damai di kerajaan, menjalani hari-hari tanpa bayang ancaman.",
        "Dan untuk pertama kalinya dalam waktu lama...",
        "Herta dapat tersenyum dengan tenang.",
        "",
        "✦ Mereka hidup bahagia selamanya. ✦",
        "",
        "Alhamdulillah udah selesai, bismillah nilai A+"
    };

    int total_lines = sizeof(story_lines) / sizeof(story_lines[0]);

    clear_story_box();
    int cur_y = 6;

    for (int idx = 0; idx < total_lines; idx++) {

        attron(COLOR_PAIR(2));
        print_story_slow(cur_y, 6, story_lines[idx], 15);
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(4));
        mvprintw(LINES - 4, COLS - 34, "[ Tekan SPACE untuk lanjut ]");
        attroff(COLOR_PAIR(4));

        refresh();

        int c;
        while (1) {
            c = getch();
            if (c == ' ' || c == '\n') break;
        }

        cur_y += 2;
    }

    attron(COLOR_PAIR(1));
    mvprintw(LINES / 2, COLS / 2 - 12, "✦ Terima kasih telah bermain ✦");
    attroff(COLOR_PAIR(1));

    refresh();
    napms(1500);
}



void stage_start(int stage_number, Player *p) {
    if(stage_number == 1){
    stage_menu(stage_number);
    stage_storybegin(stage_number); 
    stage_upgrade(stage_number, p);
    stage_background(stage_number);}

    else if(stage_number == 2){
        stage_storybegin2(stage_number);
        stage_upgrade2(stage_number, p);
    }
    else if(stage_number == 3){
        stage_storybegin3(stage_number);
        stage_upgrade3(stage_number, p);
    }
    
}
