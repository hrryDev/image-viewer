#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
struct pixel {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

struct image {
	int width;
	int height;
	struct pixel* data;
};

#endif
