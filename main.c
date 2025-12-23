#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

typedef enum Format {
	P6,
	INVALID,
} Format;

typedef struct {
	unsigned short red;
	unsigned short green;
	unsigned short blue;
} pixel_4;

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} pixel_8;

typedef struct {
	int width;
	int height;
	pixel_8* image_data;
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
	int width, height, image_data_width, max_value;
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
	image_data = (pixel_8*) malloc(image_data_width * height);

	printf("width = %d, height = %d\n\n", width, height);
	printf("pixel size = %li bytes\n", sizeof(pixel_8));
	printf("image_data_width = %d bytes\n", image_data_width);
	printf("image_data memory allocated = %d bytes\n", image_data_width * height);

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
				image_data[pixel] = pixel_buffer;
			} else {
				fprintf(stderr, "Error reading pixel data.\n");
				exit(1);
			}
		}
	}

	Image image;
	image.image_data = image_data;
	image.width = width;
	image.height = height;

	return image;
}

int main(int argc, char* argv[]) {
	FILE* file;
	Format format;
	Image image;
	SDL_Window* window;

	if (argc != 2) {
		printf("Usage: %s [filename]\n", argv[0]);
		exit(1);
	}

	file = open_file(argv[1]);
	format = read_format(file);

	switch (format) {
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

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
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

	free(image.image_data);
	SDL_Quit();
	return 0;
}
