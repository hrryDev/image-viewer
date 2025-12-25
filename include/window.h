#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

SDL_Window* init_window(const int width, const int height, const char* window_title);
// void display_image();
void put_pixel(SDL_Surface* surface, const int x, const int y, const Uint32 color);
void event_loop();

#endif // !WINDOW_H
