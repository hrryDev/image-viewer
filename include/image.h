#ifndef IMAGE_H
#define IMAGE_H

struct pixel {
	char red;
	char green;
	char blue;
};

struct image {
	int width;
	int height;
	struct pixel* data;
};

#endif
