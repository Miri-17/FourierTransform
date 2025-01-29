#include "image_size.h"
#include "file_processing.h"
#include "dft.h"
#include <stdio.h>
#include <stdlib.h>

// パワースペクトルを計算する関数.
void calculate_power_spectrum(float *real, float *imag, float *power) {
    for (int u = 0; u < N; u++) {
        for (int v = 0; v < N; v++) {
            int index = u * N + v;
            power[index] = real[index] * real[index] + imag[index] * imag[index];
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s [input] [output_real] [output_imag] [output_power]\n", argv[0]);
        exit(1);
    }

    // 動的配列の確保.
    unsigned char *input = (unsigned char*)malloc(sizeof(unsigned char) * N * N);
    float *real = (float*)malloc(sizeof(float) * N * N);
    float *imag = (float*)malloc(sizeof(float) * N * N);
    float *power = (float*)malloc(sizeof(float) * N * N);
    if (!input || !real || !imag || !power) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(input);
        free(real);
        free(imag);
        free(power);
        exit(1);
    }

    // 入力画像の読み込み.
    read_image(argv[1], input);

    // 離散フーリエ変換.
    tddft(input, real, imag);

    // パワースペクトルの計算.
    calculate_power_spectrum(real, imag, power);

    // 実部・虚部・パワースペクトル画像の書き込み.
    write_data(argv[2], real);
    write_data(argv[3], imag);
    write_data(argv[4], power);

    // 動的配列の解放.
    free(input);
    free(real);
    free(imag);
    free(power);

    printf("Processing complete.\n");
    return 0;
}
