#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "../include/audio.h"

static Mix_Music *current_music = NULL;
static char current_path[256] = "";

void play_music_once(const char *path, int loop) {
    if (strcmp(current_path, path) == 0 && Mix_PlayingMusic()) {
        return;
    }

    stop_music();

    current_music = Mix_LoadMUS(path);
    if (!current_music) {
        printf("Failed to load music: %s\n", Mix_GetError());
        return;
    }

    strcpy(current_path, path);
    Mix_PlayMusic(current_music, loop);
}


void audio_init() {
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void audio_quit() {
    stop_music();
    Mix_CloseAudio();
    SDL_Quit();
}

void play_music(const char *path, int loop) {
    if (current_music) {
        Mix_HaltMusic();
        Mix_FreeMusic(current_music);
        current_music = NULL;
    }

    current_music = Mix_LoadMUS(path);
    if (!current_music) {
        printf("Failed to load music: %s\n", Mix_GetError());
        return;
    }

    Mix_PlayMusic(current_music, loop);
}

void stop_music() {
    if (current_music) {
        Mix_HaltMusic();
        Mix_FreeMusic(current_music);
        current_music = NULL;
    }
}

void play_sfx(const char *path) {
    Mix_Chunk *sfx = Mix_LoadWAV(path);
    if (!sfx) return;

    Mix_PlayChannel(-1, sfx, 0);
}
