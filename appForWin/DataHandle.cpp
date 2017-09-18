#include "DataHandle.h"
#include <fstream>
#include <iostream>
#include "math.h"

DataHandle::DataHandle()
{
    GetFir();
}

void DataHandle::GetFir()
{
    int k;
    bool FreqCorrection=true;
    double RealHofZ[1024];
    double ImagHofZ[1024];
    int NumTaps=30;
    double FIRCoeff[1024];
    double OmegaC = 0.2;
    double BW = 0.1;
    double WinBeta=4.0;
    double ParksWidth=0.15;
    RectWinFIR(FIRCoeff, NumTaps, OmegaC, BW);
    FIRFilterWindow(FIRCoeff, NumTaps, WinBeta);
    if(FreqCorrection)
    {
        double OrigOmega = OmegaC;
        double OrigBW = BW;
        FIRFreqError(FIRCoeff, NumTaps, &OmegaC, &BW);
        RectWinFIR(FIRCoeff, NumTaps, OmegaC, BW);
        FIRFilterWindow(FIRCoeff, NumTaps,  WinBeta);
        OmegaC = OrigOmega;
        BW = OrigBW;
    }
    for(k=0; k<2048; k++)RealHofZ[k] = ImagHofZ[k] = 0.0;
    for(k=0; k<NumTaps; k++)RealHofZ[k] = FIRCoeff[k] * (double)2048;
    FFT(RealHofZ, ImagHofZ, 2048, FORWARD);

    FILE *OutputFile;
     OutputFile = fopen("FIR Filter Coeff.txt","w");
     for(int j=0; j<NumTaps; j++)
      {
       fprintf(OutputFile,"\n %9.9f ", FIRCoeff[j]);
      }
     fclose(OutputFile);
//    ofstream OutputFile("FIR Filter Coeff.txt");
//    if(OutputFile.is_open())
//    {
//        for(int j=0; j<NumTaps; j++)
//        {
//          fprintf(OutputFile,"\n %9.9f ", FIRCoeff[j]);
//        }
//        fclose(OutputFile);
//    }
//    else
//    {
//        qDebug()<<"Cannot open the outfile!\n";
//        return;
//    }
}

void DataHandle::FIRFreqError(double *Coeff, int NumTaps,
                       double *OmegaC, double *BW)
{
    int j, J3dB;
    double Omega, CorrectedOmega, Mag;
    J3dB = 10;
    for(j=0; j<1000; j++)
    {
        Omega = (double)j / 1000.0;
        Mag = Goertzel(Coeff, NumTaps, Omega);
        if(Mag > 0.707)J3dB = j;
        // J3dB will be the last j where the response was > -3 dB
        if(Mag < 0.1)break;
        // Stop when the response is down to -20 dB.
    }
    Omega = (double)J3dB / 1000.0;

    CorrectedOmega = *OmegaC * 2.0 - Omega;  // This is usually OK.
    if(CorrectedOmega < 0.001)CorrectedOmega = 0.001;
    if(CorrectedOmega > 0.99)CorrectedOmega = 0.99;
    *OmegaC = CorrectedOmega;
}

void DataHandle::RectWinFIR(double *FirCoeff, int NumTaps,
                 double OmegaC, double BW)
{
    for(int j=0; j<NumTaps; j++)
    {
        double Arg = (double)j - (double)(NumTaps-1) / 2.0;
        FirCoeff[j] = OmegaC * Sinc(OmegaC * Arg * M_PI);
    }
}

double DataHandle::Sinc(double x)
{
 if(x > -1.0E-5 && x < 1.0E-5)return(1.0);
 return(sin(x)/x);
}

// This gets used with the Kaiser window.
double DataHandle::Bessel(double x)
{
 double Sum=0.0, XtoIpower;
 int i, j, Factorial;
 for(i=1; i<10; i++)
  {
   XtoIpower = pow(x/2.0, (double)i);
   Factorial = 1;
   for(j=1; j<=i; j++)Factorial *= j;
   Sum += pow(XtoIpower / (double)Factorial, 2.0);
  }
 return(1.0 + Sum);
}

void DataHandle::FIRFilterWindow(double *FIRCoeff, int N, double Beta)
{
    int j;
     double dN, *WinCoeff;

     if(Beta < 0.0)Beta = 0.0;
     if(Beta > 10.0)Beta = 10.0;

     WinCoeff  = new(std::nothrow) double[N+2];
     if(WinCoeff == NULL)
     {
         return;
     }

     dN = N + 1;
     double Arg;
     for(j=0; j<N; j++)
     {
         Arg = Beta * sqrt(1.0 - pow( ((double)(2*j+2) - dN) / dN, 2.0) );
         WinCoeff[j] = Bessel(Arg) / Bessel(Beta);
     }

     // Fold the coefficients over.
      for(j=0; j<N/2; j++)WinCoeff[N-j-1] = WinCoeff[j];
      // Apply the window to the FIR coefficients.
      for(j=0; j<N; j++)FIRCoeff[j] *= WinCoeff[j];
      delete[] WinCoeff;
}

int DataHandle::IsValidFFTSize(int N)
{
 if(N < MINIMUM_FFT_SIZE || N > MAXIMUM_FFT_SIZE || (N & (N - 1)) != 0)return(0);   // N & (N - 1) ensures a power of 2
 return ( (int)( log((double)N) / M_LN2 + 0.5 ) );         // return M where N = 2^M
}

void DataHandle::FFT(double *InputR, double *InputI, int N, TTransFormType Type)
{
 int j, LogTwoOfN, *RevBits;
 double *BufferR, *BufferI, *TwiddleR, *TwiddleI;
 double OneOverN;

 // Verify the FFT size and type.
 LogTwoOfN = IsValidFFTSize(N);
 if(LogTwoOfN == 0 || (Type != FORWARD && Type != INVERSE) )
 {
  // ShowMessage("Invalid FFT type or size.");
  return;
 }

 // Memory allocation for all the arrays.
 BufferR  = new(std::nothrow) double[N];
 BufferI  = new(std::nothrow) double[N];
 TwiddleR = new(std::nothrow) double[N/2];
 TwiddleI = new(std::nothrow) double[N/2];
 RevBits  = new(std::nothrow) int[N];

 if(BufferR == NULL  || BufferI == NULL  ||
    TwiddleR == NULL || TwiddleI == NULL || RevBits == NULL)
  {
   // ShowMessage("FFT Memory Allocation Error");
   return;
  }

 ReArrangeInput(InputR, InputI, BufferR, BufferI, RevBits, N);
 FillTwiddleArray(TwiddleR, TwiddleI, N, Type);
 Transform(InputR, InputI, BufferR, BufferI, TwiddleR, TwiddleI, N);


 // The ReArrangeInput function swapped Input[] and Buffer[]. Then Transform()
 // swapped them again, LogTwoOfN times. Ultimately, these swaps must be done
 // an even number of times, or the pointer to Buffer gets returned.
 // So we must do one more swap here, for N = 16, 64, 256, 1024, ...
 OneOverN = 1.0;
 if(Type == FORWARD) OneOverN = 1.0 / (double)N;

 if(LogTwoOfN % 2 == 1)
  {
   for(j=0; j<N; j++) InputR[j] = InputR[j] * OneOverN;
   for(j=0; j<N; j++) InputI[j] = InputI[j] * OneOverN;
  }
 else // if(LogTwoOfN % 2 == 0) then the results are still in Buffer.
  {
   for(j=0; j<N; j++) InputR[j] = BufferR[j] * OneOverN;
   for(j=0; j<N; j++) InputI[j] = BufferI[j] * OneOverN;
  }

 delete[] BufferR;
 delete[] BufferI;
 delete[] TwiddleR;
 delete[] TwiddleI;
 delete[] RevBits;
}

void DataHandle::ReArrangeInput(double *InputR, double *InputI,
     double *BufferR, double *BufferI, int *RevBits, int N)
{
 int j, k, J, K;

 J = N/2;
 K = 1;
 RevBits[0] = 0;
 while(J >= 1)
  {
   for(k=0; k<K; k++)
    {
     RevBits[k+K] = RevBits[k] + J;
    }
   K *= 2;
   J /= 2;
  }


 // Move the rearranged input values to Buffer.
 // Take note of the pointer swaps at the top of the transform algorithm.
 for(j=0; j<N; j++)
  {
   BufferR[j] = InputR[ RevBits[j] ];
   BufferI[j] = InputI[ RevBits[j] ];
  }

}

double DataHandle::Goertzel(double *Samples, int N, double Omega)
{
 int j;
 double Reg0, Reg1, Reg2;        // 3 shift registers
 double CosVal, Mag;
 Reg1 = Reg2 = 0.0;

 CosVal = 2.0 * cos(M_PI * Omega );
 for (j=0; j<N; j++)
  {
   Reg0 = Samples[j] + CosVal * Reg1 - Reg2;
   Reg2 = Reg1;  // Shift the values.
   Reg1 = Reg0;
  }
 Mag = Reg2 * Reg2 + Reg1 * Reg1 - CosVal * Reg1 * Reg2;

 if(Mag > 0.0)Mag = sqrt(Mag);
 else Mag = 1.0E-12;

 return(Mag);
}

void DataHandle::FillTwiddleArray(double *TwiddleR, double *TwiddleI,
                      int N, TTransFormType Type)
{
 int j;
 double Theta, TwoPiOverN;

 TwoPiOverN = M_2PI / (double) N;

 if(Type == FORWARD)
  {
   TwiddleR[0] = 1.0;
   TwiddleI[0] = 0.0;
   TwiddleR[N/4] = 0.0;
   TwiddleI[N/4] = -1.0;
   TwiddleR[N/8] = M_SQRT_2;
   TwiddleI[N/8] = -M_SQRT_2;
   TwiddleR[3*N/8] = -M_SQRT_2;
   TwiddleI[3*N/8] = -M_SQRT_2;
   for(j=1; j<N/8; j++)
    {
     Theta = (double)j * -TwoPiOverN;
     TwiddleR[j] = cos(Theta);
     TwiddleI[j] = sin(Theta);
     TwiddleR[N/4-j] = -TwiddleI[j];
     TwiddleI[N/4-j] = -TwiddleR[j];
     TwiddleR[N/4+j] = TwiddleI[j];
     TwiddleI[N/4+j] = -TwiddleR[j];
     TwiddleR[N/2-j] = -TwiddleR[j];
     TwiddleI[N/2-j] = TwiddleI[j];
    }
  }

 else
  {
   TwiddleR[0] = 1.0;
   TwiddleI[0] = 0.0;
   TwiddleR[N/4] = 0.0;
   TwiddleI[N/4] = 1.0;
   TwiddleR[N/8] = M_SQRT_2;
   TwiddleI[N/8] = M_SQRT_2;
   TwiddleR[3*N/8] = -M_SQRT_2;
   TwiddleI[3*N/8] = M_SQRT_2;
   for(j=1; j<N/8; j++)
    {
     Theta = (double)j * TwoPiOverN;
     TwiddleR[j] = cos(Theta);
     TwiddleI[j] = sin(Theta);
     TwiddleR[N/4-j] = TwiddleI[j];
     TwiddleI[N/4-j] = TwiddleR[j];
     TwiddleR[N/4+j] = -TwiddleI[j];
     TwiddleI[N/4+j] = TwiddleR[j];
     TwiddleR[N/2-j] = -TwiddleR[j];
     TwiddleI[N/2-j] = TwiddleI[j];
    }
  }

}

//---------------------------------------------------------------------------

// The Fast Fourier Transform.
void DataHandle::Transform(double *InputR, double *InputI,
               double *BufferR, double *BufferI,
               double *TwiddleR, double *TwiddleI, int N)
{
 int j, k, J, K, I, T;
 double *TempPointer;
 double TempR, TempI;

 J = N/2;     // J increments down to 1
 K = 1;       // K increments up to N/2
 while(J > 0) // Loops Log2(N) times.
  {
   // Swap pointers, instead doing this: for(j=0; j<N; j++) Input[j] = Buffer[j];
   // We start with a swap because of the swap in ReArrangeInput.
   TempPointer = InputR;
   InputR = BufferR;
   BufferR = TempPointer;
   TempPointer = InputI;
   InputI = BufferI;
   BufferI = TempPointer;

   I = 0;
   for(j=0; j<J; j++)
    {
     T = 0;
     for(k=0; k<K; k++) // Loops N/2 times for every value of J and K
      {
       TempR = InputR[K+I] * TwiddleR[T] - InputI[K+I] * TwiddleI[T];
       TempI = InputR[K+I] * TwiddleI[T] + InputI[K+I] * TwiddleR[T];
       BufferR[I]   = InputR[I] + TempR;
       BufferI[I]   = InputI[I] + TempI;
       BufferR[I+K] = InputR[I] - TempR;
       BufferI[I+K] = InputI[I] - TempI;
       I++;
       T += J;
      }
     I += K;
    }
   K *= 2;
   J /= 2;
  }

}







































