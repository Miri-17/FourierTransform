#include "file_processing.h"
#include <stdio.h>
#include <stdlib.h>

void read_image(const char *filename, unsigned char *image) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error: Unable to open input file.\n");
        exit(1);
    }
    fread(image, sizeof(unsigned char), N * N, file);
    fclose(file);
}

void write_data(const char *filename, float *data) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Error: Unable to open output file.\n");
        exit(1);
    }
    fwrite(data, sizeof(float), N * N, file);
    fclose(file);
}

void read_data(const char *filename, float *data) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error: Unable to open input file.\n");
        exit(1);
    }
    fread(data, sizeof(float), N * N, file);
    fclose(file);
}
