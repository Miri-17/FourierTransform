#include "image_size.h"
#include "file_processing.h"
#include "dft.h"
#include <stdio.h>
#include <stdlib.h>

// 縦方向の周期的な雑音を除去する関数.
void apply_filter(float *real, float *imag, int range, int step) {
    if (range < 1 || range > 127 || step < 1) {
        fprintf(stderr, "Error: Invalid filter parameters.\n");
        // メモリの解放を行わないため、ここではexit()していません.
        return;
    }

    for (int y = 128 - range; y < 128 + range; y++) {
        for (int x = 0; x < N; x += step) {
            real[y * N + x] = 0;
            imag[y * N + x] = 0;
        }
    }
}

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
    if (argc != 6) {
        fprintf(stderr, "Usage: %s [input_shifted_real] [input_shifted_imag] [output_image] [range (1-127)] [step (1-)]\n", argv[0]);
        exit(1);
    }

    // 動的配列の確保.
    float *shifted_real = (float*)malloc(sizeof(float) * N * N);
    float *shifted_imag = (float*)malloc(sizeof(float) * N * N);
    float *output_real = (float*)malloc(sizeof(float) * N * N);
    float *output_imag = (float*)malloc(sizeof(float) * N * N);
    if (!shifted_real || !shifted_imag || !output_real || !output_imag) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(shifted_real);
        free(shifted_imag);
        free(output_real);
        free(output_imag);
        exit(1);
    }
    int range = atoi(argv[4]);
    int step = atoi(argv[5]);

    // 実部画像の読み込み.
    read_data(argv[1], shifted_real);
    // 虚部画像の読み込み.
    read_data(argv[2], shifted_imag);

    // ローパスフィルタの適用.
    apply_filter(shifted_real, shifted_imag, range, step);

    // 中心にある直流成分の位置を元に戻す.
    shift_spectrum(shifted_real);
    shift_spectrum(shifted_imag);

    // 逆フーリエ変換.
    tdidft(shifted_real, shifted_imag, output_real, output_imag);
    
    // 結果画像の書き込み.
    write_data(argv[3], output_real);

    // 動的配列の解放.
    free(shifted_real);
    free(shifted_imag);
    free(output_real);
    free(output_imag);

    printf("Processing complete.\n");
    return 0;
}
