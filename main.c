#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

void handleEvent(SDL_Event e) {
	if (e.type == SDL_KEYDOWN) {
		printf("Keyboard button pressed");
	}
}

int initWindow(const int width, const int height) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("SDL_Init Error: %s", SDL_GetError());
		return 0;
	}
	
	SDL_Window *window;
	SDL_CreateWindow("Image Viewer",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					width, height, 0);

	return 1;
}

int main(int argc, char* argv[]) {
	if (!initWindow(640, 480)) {
		return 0;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0 , 255);

	// Clear Window (creates a red background)
	SDL_RenderClear(renderer);

	SDL_Rect rect;
	rect.x = 50;
	rect.y = 50;
	rect.w = 50;
	rect.h = 50;

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &rect);

	SDL_RenderPresent(renderer);

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			handleEvent(event);
		}
	}

	SDL_Quit();
	return 0;
}
