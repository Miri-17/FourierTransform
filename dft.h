#ifndef DFT_H
#define DFT_H

#include "image_size.h"

// 2次元離散フーリエ変換 (Two-Dimensional Discrete Fourier Transform) を行う関数.
void tddft(unsigned char *input, float *real, float *imag);

// 1次元離散フーリエ変換 (One-Dimensional Discrete Fourier Transform) を行う関数.
void oddft(float *fr, float *fi, float *real, float *imag);

// 2次元逆離散フーリエ変換 (Two-Dimensional Inverse Discrete Fourier Transform) を行う関数.
void tdidft(float *input_real, float *input_imag, float *real, float *imag);

// 1次元逆離散フーリエ変換 (One-Dimensional Inverse Discrete Fourier Transform) を行う関数.
void odidft(float *fr, float *fi, float *real, float *imag);

#endif
