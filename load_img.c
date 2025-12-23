#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} ppm_pixel;

FILE* open_file(const char *filename) {
	FILE* file;
	file = fopen(filename, "r");
	
	if (file == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	return file;
}

void read_ppm(FILE* file, const int width, const int height) {
	int line_width, max_value;
	// 3 (color channels) * 8 (bits/channel) = 24
	line_width = width * 24;
	char line[line_width];

	// Read max value TODO: figure out what this would be used for
	fgets(line, sizeof(line), file);
	max_value = atoi(line);
	
	// Reading pixel data.
	ppm_pixel pixel_buffer;
	size_t bytesRead;
	ppm_pixel image_data[width * height];

	int count = 0;
	for (int row = 0; row < height; ++row) {
		for (int pixel = 0; pixel < width; ++pixel) {
			++count;
			bytesRead = fread(&pixel_buffer, sizeof(ppm_pixel), 1, file);

			if (bytesRead == 1) {
				printf("\nPixel %d read.\n", count);
				printf("Red = %d\n", pixel_buffer.red);
				printf("Green = %d\n", pixel_buffer.green);
				printf("Blue = %d\n\n", pixel_buffer.blue);
				image_data[pixel] = pixel_buffer;
			} else {
				fprintf(stderr, "Error reading pixel data.\n");
				exit(1);
			}
		}
	}

	fclose(file);
}

int main(const int argc, const char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s [filename]\n", argv[0]);
		exit(1);
	}

	int width, height;
	char line[256];
	FILE* file;
	file = open_file(argv[1]);

	// Reading format.
	fgets(line, sizeof(line), file);
	if (strcmp(line, "P6\n") == 0) {
		printf("Image is in PPM format\n");
	}

	// Clearing comment lines.
	fgets(line, sizeof(line), file);
	while (line[0] == '#' || line[0] == '\n') {
		fgets(line, sizeof(line), file);
	}
	
	sscanf(line, "%d %d", &width, &height);
	printf("width = %d, height = %d\n", width, height);

	read_ppm(file, width, height);

	return 0;
}
