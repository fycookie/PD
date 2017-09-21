#ifndef CFFT_H
#define CFFT_H
#include "complex.h"
// 最大FFT样本数
#define MAX_FFT_SIZE 15000

#ifndef PI
#define PI 3.14159265358979323846
#endif

// 指数计算
const int POW[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};

// 旋转因子
static Complex W[MAX_FFT_SIZE/2];

int LOG(int n);
void GenerateRotationFactor( int size );
void ArrayCopy(Complex dest[], Complex src[], int size);
void BitReverse(int inIndex[], int indexSize);
void CFFT(double CIN[], double COUT[], int SIZE);
void FFT(Complex IN[], Complex OUT[], int Size);

#endif // CFFT_H
