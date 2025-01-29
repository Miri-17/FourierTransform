#include "image_size.h"
#include "file_processing.h"
#include <stdio.h>
#include <stdlib.h>

// スペクトル画像の左上と右下、右上と左下を入れ替える関数.
void shift_spectrum(float *data) {
    int half_height = N / 2;
    int half_width = N / 2;
    float temp = 0;
    
    for (int y = 0; y < half_height; y++) {
        for (int x = 0; x < half_width; x++) {
            // 左上と右下を入れ替え.
            temp = data[y * N + x];
            data[y * N + x] = data[(y + half_height) * N + (x + half_width)];
            data[(y + half_height) * N + (x + half_width)] = temp;

            // 右上と左下を入れ替え.
            temp = data[y * N + (x + half_width)];
            data[y * N + (x + half_width)] = data[(y + half_height) * N + x];
            data[(y + half_height) * N + x] = temp;
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s [input_real] [input_imag] [input_power] [output_prefix]\n", argv[0]);
        exit(1);
    }

    // 動的配列の確保.
    float *real = (float*)malloc(sizeof(float) * N * N);
    float *imag = (float*)malloc(sizeof(float) * N * N);
    float *power = (float*)malloc(sizeof(float) * N * N);
    if (!real || !imag || !power) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(real);
        free(imag);
        free(power);
        exit(1);
    }

    // 実部画像の読み込み.
    read_data(argv[1], real);
    // 虚部画像の読み込み.
    read_data(argv[2], imag);
    // パワースペクトル画像の読み込み.
    read_data(argv[3], power);

    // スペクトル画像を中心に直流成分が来るように並び替え.
    shift_spectrum(real);
    shift_spectrum(imag);
    shift_spectrum(power);

    // 出力画像の名前の確定.
    char real_output[256], imag_output[256], power_output[256];
    snprintf(real_output, sizeof(real_output), "%s_%s", argv[4], argv[1]);
    snprintf(imag_output, sizeof(imag_output), "%s_%s", argv[4], argv[2]);
    snprintf(power_output, sizeof(power_output), "%s_%s", argv[4], argv[3]);

    // 実部・虚部・パワースペクトルを並べ替えた後の画像の書き込み.
    write_data(real_output, real);
    write_data(imag_output, imag);
    write_data(power_output, power);

    // 動的配列の解放.
    free(real);
    free(imag);
    free(power);

    printf("Processing complete.\n");
    return 0;
}
