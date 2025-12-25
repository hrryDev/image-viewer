#include "ppm.h"
#include "image.h"

#include <stddef.h>
#include <stdlib.h>

struct ppm_header read_header(FILE *file) {
	char line[256];

	struct ppm_header header;
	
	// Skipping over comment lines
	fgets(line, sizeof(line), file);
	while (line[0] == '#' || line[0] == '\n') {
		fgets(line, sizeof(line), file);
	}

	sscanf(line, "%d %d", &header.width, &header.height);
	
	// Read max value
	fgets(line, sizeof(line), file);
	header.max_value = atoi(line);

	header.data_width = sizeof(struct pixel) * header.width;
	header.size_of_image_data = header.data_width * header.height;

	return header;
}

struct image get_image_data(FILE *file, const struct ppm_header header) {
	int count;
	struct pixel pixel_buffer;
	struct pixel* pixel_data;
	struct image image;

	size_t bytesRead;

	count = 0;
	image.width = header.width;
	image.height = header.height;
	image.data = (struct pixel*) malloc(header.size_of_image_data);

	for (int row = 0; row < header.height; ++row) {
		for (int pixel = 0; pixel < header.width; ++pixel) {
			++count;
			bytesRead = fread(&pixel_buffer, sizeof(struct pixel), 1, file);

			if (bytesRead) {
				image.data[count] = pixel_buffer;
				printf("Read pixel %d: %d %d %d\n", count, image.data[count].red, image.data[count].green, image.data[count].blue);
			} else {
				fprintf(stderr, "ERROR: Could not read pixel data\n");
				free(image.data);
				exit(1);
			}
		}
	}

	return image;
}
