#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>

enum format {
	P6,
	INVALID,
};

FILE* open_file(const char* filename);
enum format read_format(FILE* file);

#endif /* FILE_UTILS_H */
