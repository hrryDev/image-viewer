#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL_video.h>

SDL_Window* init_window(int width, int height);
void put_pixels(SDL_Surface* surface, int x, int y, Uint32 color);

#endif // !WINDOW_H
