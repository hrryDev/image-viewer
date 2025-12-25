#include "file_utils.h"

#include <stdlib.h>
#include <string.h>

FILE* open_file(const char* filename) {
	FILE* file;
	file = fopen(filename, "r");

	if (file == NULL) {
		fprintf(stderr, "ERRO: Could not open file\n");
		exit(1);
	}

	return file;
}

enum format read_format(FILE* file) {
	char line[256];

	fgets(line, sizeof(line), file);

	if (strcmp(line, "P6\n") == 0) {
		printf("Image is in PPM format\n");
		return P6;
	}

	fprintf(stderr, "ERROR: This image format is not supported.");
	return INVALID;
}
