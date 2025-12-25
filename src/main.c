#include "file_utils.h"
#include "window.h"
#include "ppm.h"

#include <SDL_pixels.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <stdio.h>

struct image ppm(FILE* file) {
	struct ppm_header header;
	struct image image;

	header = read_header(file);
	image = get_image_data(file, header);

	return image;
}

void display_image(SDL_Window* window, SDL_Surface* surface, SDL_PixelFormat* surface_format, const struct image image) {
	Uint32 color;

	SDL_LockSurface(surface);

	for (int row = 0; row < image.height; ++row) {
		for (int col = 0; col < image.width; ++col) {
			int index = row * image.width + col;
			color = SDL_MapRGB(surface_format, image.data[index].red, image.data[index].green, image.data[index].blue);
			put_pixel(surface, col, row, color);
		}
	}

	SDL_UnlockSurface(surface);
	SDL_UpdateWindowSurface(window);
}

int main(const int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
		exit(1);
	}

	char* filename;
	FILE* file;

	enum format file_format;
	struct image image;

	SDL_Window* window;
	SDL_Surface* surface;
	SDL_PixelFormat* surface_format;

	filename = argv[1];
	file = open_file(filename);
	file_format = read_format(file);

	switch (file_format) {
		case P6:
			image = ppm(file);
			break;
		case INVALID:
			fclose(file);
			exit(2);
			break;
	}

	fclose(file);

	window = init_window(image.width, image.height, filename);
	surface = SDL_GetWindowSurface(window);
	surface_format = surface->format;

	display_image(window, surface, surface_format, image);
	event_loop();

	free(image.data);
	SDL_Quit();
	return 0;
}
