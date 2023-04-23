#ifndef __UTIL_IMG__
#define __UTIL_IMG__

#include <cstdio>

const int ImgOffset = 1078; // 全色图的主体偏移
const int ImgSive = 8000, height = 100, width = 80; // 全色图的主体偏移
const char *READB = "rb";

typedef unsigned char U1;

void input_img8(const char *name, U1 *img); // 输入图像像素
void compress(const U1 *img, double *cpimg); // 压缩像素16倍
void nocompress(const U1 *img, double *cpimg); // 不压缩，仅仅转double

void input_img8(const char *name, U1 *img) {
    FILE *fp = fopen(name, READB);
    if (fp == 0) {
        printf("no!!!!\n");
        exit(0);
    }
    fseek(fp, ImgOffset, SEEK_SET);
    fread(img, 1, ImgSive, fp);
    fclose(fp);
} // 一个输入图像的小模块罢了


void compress(const U1 *img, double *cpimg) {
    int cnt = 0;
    for (int i = 0; i < height; i += 4) {
        for (int j = 0; j < width; j += 4) {
            cpimg[cnt] = 0;
            cpimg[cnt] += img[(i + 0) * width + j + 0];
            cpimg[cnt] += img[(i + 0) * width + j + 1];
            cpimg[cnt] += img[(i + 0) * width + j + 2];
            cpimg[cnt] += img[(i + 0) * width + j + 3];

            cpimg[cnt] += img[(i + 1) * width + j + 0];
            cpimg[cnt] += img[(i + 1) * width + j + 1];
            cpimg[cnt] += img[(i + 1) * width + j + 2];
            cpimg[cnt] += img[(i + 1) * width + j + 3];
            
            cpimg[cnt] += img[(i + 2) * width + j + 0];
            cpimg[cnt] += img[(i + 2) * width + j + 1];
            cpimg[cnt] += img[(i + 2) * width + j + 2];
            cpimg[cnt] += img[(i + 2) * width + j + 3];
            
            cpimg[cnt] += img[(i + 3) * width + j + 0];
            cpimg[cnt] += img[(i + 3) * width + j + 1];
            cpimg[cnt] += img[(i + 3) * width + j + 2];
            cpimg[cnt] += img[(i + 3) * width + j + 3];
            cpimg[cnt] /= 16.0;
            cnt ++;
        }
    }
}

void nocompress(const U1 *img, double *cpimg) {
    for (int i = 0; i < ImgSive; ++i) {
        cpimg[i] = img[i];
    }
}

#endif