#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H

#include "image_size.h"

// 入力画像データを読み込む関数.
void read_image(const char *filename, unsigned char *image);

// 画像データをファイルに書き出す関数.
void write_data(const char *filename, float *data);

// 入力画像データをファイルから読み込む関数.
void read_data(const char *filename, float *data);

#endif
