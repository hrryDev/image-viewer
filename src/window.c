#include "window.h"
#include <SDL_video.h>

SDL_Window* init_window(const int width, const int height, const char* window_title) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("SDL_Init Error: %s", SDL_GetError());
		return 0;
	}

	SDL_Window* window;
	window = SDL_CreateWindow(window_title,
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					width, height, 0);

	return window;
}

void put_pixel(SDL_Surface* surface, const int x, const int y, const Uint32 color) {
	Uint8 * pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = color;
}
