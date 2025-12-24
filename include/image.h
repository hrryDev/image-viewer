#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

typedef struct Image {
	int width;
	int height;
	Uint32 data;
} Image;

#endif

