#ifndef AUDIO_H
#define AUDIO_H

void audio_init();
void audio_quit();

void play_music(const char *path, int loop);
void stop_music();

void play_sfx(const char *path);
void play_music_once(const char *path, int loop);


#endif
