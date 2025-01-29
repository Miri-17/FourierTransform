#include "image_size.h"
#include "file_processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// パワースペクトル画像に対数を適用する関数.
void apply_log_scale(float *shifted_power, float *log_power) {
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            log_power[y * N + x] = log(shifted_power[y * N + x]);
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [input_shifted_power] [output_log_power]\n", argv[0]);
        exit(1);
    }

    // 動的配列の確保.
    float *shifted_power = (float*)malloc(sizeof(float) * N * N);
    float *log_power = (float*)malloc(sizeof(float) * N * N);
    if (!shifted_power || !log_power) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(shifted_power);
        free(log_power);
        exit(1);
    }

    // 入力パワースペクトル画像の読み込み.
    read_data(argv[1], shifted_power);

    // パワースペクトルに対数を適用.
    apply_log_scale(shifted_power, log_power);

    // 結果画像の書き込み.
    write_data(argv[2], log_power);

    // 動的配列の解放.
    free(shifted_power);
    free(log_power);

    printf("Processing complete.\n");
    return 0;
}
