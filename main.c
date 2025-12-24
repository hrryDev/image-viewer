#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

typedef enum Format {
	P6,
	INVALID,
} Format;

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} pixel_8;

typedef struct {
	int width;
	int height;
	pixel_8* data;
} Image;

SDL_Window* initWindow(const int width, const int height) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		SDL_Log("SDL_Init Error: %s", SDL_GetError());
		return 0;
	}
	
	SDL_Window *window;
	window = SDL_CreateWindow("Image Viewer",
					SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED,
					width, height, 0);

	return window;
}

FILE* open_file(const char *filename) {
	FILE* file;
	file = fopen(filename, "r");
	
	if (file == NULL) {
		printf("Error opening file\n");
		exit(3);
	}

	return file;
}

Format read_format(FILE* file) {
	char line[256];

	fgets(line, sizeof(line), file);
	
	if (strcmp(line, "P6\n") == 0) {
		printf("Image is in PPM format\n");
		return P6;
	}

	fprintf(stderr, "ERROR: This image format is not supported.");
	return INVALID;
}

Image read_ppm(FILE* file) {
	int width, height, image_data_width, max_value, size_of_image_data;
	char line[256];

	pixel_8 pixel_buffer;
	pixel_8* image_data;
	size_t bytesRead;

	// Skipping over comment lines
	fgets(line, sizeof(line), file);
	while (line[0] == '#' || line[0] == '\n') {
		fgets(line, sizeof(line), file);
	}

	sscanf(line, "%d %d", &width, &height);
	image_data_width = sizeof(pixel_8) * width;
	size_of_image_data = sizeof(pixel_8) * width * height;
	image_data = (pixel_8*) malloc(size_of_image_data);

	printf("width = %d, height = %d\n\n", width, height);
	printf("pixel size = %li bytes\n", sizeof(pixel_8));
	printf("image_data_width = %d bytes\n", image_data_width);
	printf("image_data memory allocated = %d bytes\n", size_of_image_data);

	// Read max value TODO: figure out what this would be used for
	fgets(line, sizeof(line), file);
	max_value = atoi(line);
	printf("max_value = %d\n\n", max_value);

	// Reading pixel data
	int count = 0;
	for (int row = 0; row < height; ++row) {
		for (int pixel = 0; pixel < width; ++pixel) {
			++count;
			bytesRead = fread(&pixel_buffer, sizeof(pixel_8), 1, file);

			if (bytesRead == 1) {
				// printf("Pixel %d:\n", count);
				// printf("  Red = %d\n", pixel_buffer.red);
				// printf("Green = %d\n", pixel_buffer.green);
				// printf(" Blue = %d\n\n", pixel_buffer.blue);
				image_data[count] = pixel_buffer;
			} else {
				fprintf(stderr, "Error reading pixel data.\n");
				exit(1);
			}
		}
	}

	Image image;
	image.data = image_data;
	image.width = width;
	image.height = height;


	// for (int row = 0; row < width; ++row) {
	// 	for (int col = 0; col < height; ++col) {
	// 		int index = row * width + col;
	// 		printf("(%d, %d)\nr=%d g=%d b=%d\n", row, col, image_data[index].red, image_data[index].green, image_data[index].blue);
	// 	}
	// 	printf("\n");
	// }

	return image;
}

void put_pixel(SDL_Surface* surface, int x, int y, Uint32 colour) {
	Uint8 * pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	*((Uint32*)pixel) = colour;
}

int main(int argc, char* argv[]) {
	Uint32 colour;
	FILE* file;
	Format file_format;
	Image image;
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_PixelFormat* surface_format;

	if (argc != 2) {
		printf("Usage: %s [filename]\n", argv[0]);
		exit(1);
	}

	file = open_file(argv[1]);
	file_format = read_format(file);

	switch (file_format) {
		case P6:
			image = read_ppm(file);
			break;
		case INVALID:
			exit(2);
			break;
		default:
			fprintf(stderr, "ERROR: Could not read file format.");
			break;
	}

	fclose(file);

	window = initWindow(image.width, image.height);
	
	if (!window) {
		fprintf(stderr, "Error initializing window, quitting.");
		exit(3);
	}

	surface = SDL_GetWindowSurface(window);
	surface_format = surface->format;
	SDL_LockSurface(surface);

	for (int row = 0; row < image.height; ++row) {
		for (int col = 0; col < image.width; ++col) {
			int index = row * image.width + col;
			colour = SDL_MapRGB(surface_format, image.data[index].red, image.data[index].green, image.data[index].blue);
			put_pixel(surface, col, row, colour);
		}
	}
	
	SDL_UnlockSurface(surface);
	SDL_UpdateWindowSurface(window);

	// SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	//	SDL_SetRenderDrawColor(renderer, 255, 0, 0 , 255);

	// // Clear Window (creates a red background)
	// SDL_RenderClear(renderer);

	// SDL_Rect rect;
	// rect.x = 50;
	// rect.y = 50;
	// rect.w = 50;
	// rect.h = 50;

	// SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	// SDL_RenderFillRect(renderer, &rect);

	// SDL_RenderPresent(renderer);

	SDL_Event event;
	bool quit = false;
	while (!quit) {
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
	}

	free(image.data);
	SDL_Quit();
	return 0;
}
