#ifndef PPM_H
#define PPM_H

#include <stdio.h>

#include "image.h"

struct ppm_header {
	int width;
	int height;
	int max_value;
};

ppm_header read_header(FILE* file);
image get_image_data(FILE* file);

#endif // !PPM_H
