#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct ppm_pixel {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

FILE* open_file(const char *filename) {
	FILE* file;
	file = fopen(filename, "r");

	if (file == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	return file;
}

void read_ppm(FILE* file, const int width) {
	char line[width];

	while (fgets(line, sizeof(line), file)) {
		printf("%s", line);
	}

	fclose(file);
}

int main(const int argc, const char *argv[]) {
	if (argc != 2) {
		printf("Usage: %s [filename]\n", argv[0]);
		exit(1);
	}

	int width;
	char format[256];
	FILE* file;
	file = open_file(argv[1]);

	// fgets(format, sizeof(format), file);
	// if (strcmp(format, "P6") != 0) {
	// 	fprintf(stderr, "Invalid PPM format\n");
	// 	fclose(file);
	// 	return 1;
	// }

	char line[256];
	fgets(line, sizeof(line), file);
	while (line[0] == '#') {
		fgets(line, sizeof(line), file);
	}
	
	width = atoi(strtok(line, " "));

	read_ppm(file, width);

	return 1;
}
