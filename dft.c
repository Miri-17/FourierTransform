#include "dft.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926535
#endif

void tddft(unsigned char *input, float *real, float *imag) {
    // 動的配列の確保.
    float *fr = (float*)malloc(sizeof(float) * N * N);
    float *fi = (float*)malloc(sizeof(float) * N * N);
    // 行方向の1次元DFTを行った後の実部画像と虚部画像の値を保持する変数.
    float *temp_real = (float*)malloc(sizeof(float) * N * N);
    float *temp_imag = (float*)malloc(sizeof(float) * N * N);
    // oddft() に渡すrealとimag (行にも列にもなる).
    float *output_real = (float*)malloc(sizeof(float) * N * N);
    float *output_imag = (float*)malloc(sizeof(float) * N * N);
    if (!fr || !fi || !temp_real || !temp_imag || !output_real || !output_imag) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(fr);
        free(fi);
        free(temp_real);
        free(temp_imag);
        free(output_real);
        free(output_imag);
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        output_real[i] = 0;
        output_imag[i] = 0;
    }

    // 行方向の1次元DFT.
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            fr[x] = input[y * N + x];
            fi[x] = 0;
        }

        oddft(fr, fi, output_real, output_imag);
        for (int x = 0; x < N; x++) {
            temp_real[y * N + x] = output_real[x];
            temp_imag[y * N + x] = output_imag[x];
        }
    }

    for (int i = 0; i < N; i++) {
        output_real[i] = 0;
        output_imag[i] = 0;
    }
    
    // 列方向の1次元DFT.
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            fr[y] = temp_real[y * N + x];
            fi[y] = temp_imag[y * N + x];
        }

        oddft(fr, fi, output_real, output_imag);
        for (int y = 0; y < N; y++) {
            real[y * N + x] = output_real[y];
            imag[y * N + x] = output_imag[y];
        }
    }

    // 動的配列の解放.
    free(fr);
    free(fi);
    free(temp_real);
    free(temp_imag);
    free(output_real);
    free(output_imag);
}

void oddft(float *fr, float *fi, float *real, float *imag) {
    // u または v 方向に走査.
    for (int n = 0; n < N; n++) {
        real[n] = 0;
        imag[n] = 0;
        // x または y 方向に走査.
        for (int k = 0; k < N; k++) {
            float angle = 2.0 * M_PI * n * k / N;
            real[n] += fr[k] * cos(angle) + fi[k] * sin(angle);
            imag[n] += fi[k] * cos(angle) - fr[k] * sin(angle);
        }
        real[n] /= N;
        imag[n] /= N;
    }
}

void tdidft(float *input_real, float *input_imag, float *real, float *imag) {
    // 動的配列の確保.
    float *fr = (float*)malloc(sizeof(float) * N * N);
    float *fi = (float*)malloc(sizeof(float) * N * N);
    // 行方向の1次元DFTを行った後の実部画像と虚部画像の値を保持する変数.
    float *temp_real = (float*)malloc(sizeof(float) * N * N);
    float *temp_imag = (float*)malloc(sizeof(float) * N * N);
    // oddft() に渡すrealとimag (行にも列にもなる).
    float *output_real = (float*)malloc(sizeof(float) * N * N);
    float *output_imag = (float*)malloc(sizeof(float) * N * N);
    if (!fr || !fi || !temp_real || !temp_imag || !output_real || !output_imag) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(fr);
        free(fi);
        free(temp_real);
        free(temp_imag);
        free(output_real);
        free(output_imag);
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        output_real[i] = 0;
        output_imag[i] = 0;
    }

    // 列方向の1次元DFT.
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            fr[y] = input_real[y * N + x];
            fi[y] = input_imag[y * N + x];
        }

        odidft(fr, fi, output_real, output_imag);
        for (int y = 0; y < N; y++) {
            temp_real[y * N + x] = output_real[y];
            temp_imag[y * N + x] = output_imag[y];
        }
    }

    for (int i = 0; i < N; i++) {
        output_real[i] = 0;
        output_imag[i] = 0;
    }

    // 行方向の1次元DFT.
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            fr[x] = temp_real[y * N + x];
            fi[x] = temp_imag[y * N + x];
        }

        odidft(fr, fi, output_real, output_imag);
        for (int x = 0; x < N; x++) {
            real[y * N + x] = output_real[x];
            imag[y * N + x] = output_imag[x];
        }
    }

    // 動的配列の解放.
    free(fr);
    free(fi);
    free(temp_real);
    free(temp_imag);
    free(output_real);
    free(output_imag);
}

void odidft(float *fr, float *fi, float *real, float *imag) {
    // u または v 方向に走査.
    for (int n = 0; n < N; n++) {
        real[n] = 0;
        imag[n] = 0;
        // x または y 方向に走査.
        for (int k = 0; k < N; k++) {
            float angle = 2.0 * M_PI * n * k / N;
            real[n] += fr[k] * cos(angle) - fi[k] * sin(angle);
            imag[n] += fi[k] * cos(angle) + fr[k] * sin(angle);
        }
    }
}
