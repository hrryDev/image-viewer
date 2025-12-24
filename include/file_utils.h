#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>

typedef enum Format {
	P6,
	INVALID,
} Format;

FILE* open_file(const char* filename);
Format read_format(FILE* file);

#endif /* FILE_UTILS_H */
