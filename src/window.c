#include "window.h"
#include <SDL_video.h>

SDL_Window* init_window(const int width, const int height, const char* window_title) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("SDL_Init Error: %s", SDL_GetError());
		exit(1);
	}

	SDL_Window* window;
	window = SDL_CreateWindow(window_title,
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					width, height, 0);

	if (!window) {
		fprintf(stderr, "Error initializing window, quitting.");
		exit(1);
	}

	return window;
}

void put_pixel(SDL_Surface* surface, const int x, const int y, const Uint32 color) {
	Uint8 * pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = color;
}

void event_loop() {
	SDL_Event event;
	int quit = 0;
	while (!quit) {
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = 1;
			}
		}
	}
}
