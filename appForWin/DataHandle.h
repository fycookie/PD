#ifndef DATAHANDLE_H
#define DATAHANDLE_H

#include <QDebug>

class DataHandle
{
public:
    DataHandle();
    ~DataHandle() {}
public:
    void GetFir();
    void RectWinFIR(double *FirCoeff, int NumTaps,
                    double OmegaC, double B);
    void FIRFilterWindow(double *FIRCoeff, int N, double Beta);
private:
     enum TTransFormType {FORWARD, INVERSE};
     void FIRFreqError(double *Coeff, int NumTaps,
                       double *OmegaC, double *BW);
     void FFT(double *InputR, double *InputI,
              int N, TTransFormType Type);
     void ReArrangeInput(double *InputR, double *InputI,
          double *BufferR, double *BufferI, int *RevBits, int N);
     void Transform(double *InputR, double *InputI,
                    double *BufferR, double *BufferI,
                    double *TwiddleR, double *TwiddleI, int N);
     void FillTwiddleArray(double *TwiddleR, double *TwiddleI,
                           int N, TTransFormType Type);
     double Goertzel(double *Samples, int N, double Omega);
     double Sinc(double x);
     int IsValidFFTSize(int N);
     double Bessel(double x);
};

#define M_PI        3.14159265358979323846      // Pi
#define M_2PI     6.28318530717958647692   // 2*Pi
#define M_SQRT_2  0.707106781186547524401  // sqrt(2)/2
#define MAXIMUM_FFT_SIZE  1048576
#define MINIMUM_FFT_SIZE  8

#endif // DATAHANDLE_H
