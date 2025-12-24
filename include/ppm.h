#ifndef PPM_H
#define PPM_H

#include "image.h"

#include <stdio.h>

struct ppm_header {
	int width;
	int height;
	int max_value;
	int data_width;
	int size_of_image_data;
};

struct ppm_header read_header(FILE* file);
struct image get_image_data(FILE* file, const struct ppm_header header);

#endif // !PPM_H
