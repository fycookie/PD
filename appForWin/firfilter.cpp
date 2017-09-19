#include "firfilter.h"
#include "constants.h"
#include <fstream>
#include "FFTCode.h"
#include "FIRFilterCode.h"

FIRfilter::FIRfilter()
{

}

void FIRfilter::FIRCall(void)
{
 int k;
 bool FreqCorrection = true;          // Frequency correction is usually desired, but don't use it with an AllPass filter.
 double RealHofZ[NUM_SAMPLES];       // Real and imag parts of H(z). Used with the FFT.
 double ImagHofZ[NUM_SAMPLES];
 int NumTaps = 30;                    // 4 <= NumTaps < 256 for windowed FIR
                                      // Should be odd for windowed high pass.
                                      // 9 <= NumTaps < 127 for Parks McClellan
                                      // Must be odd for Parks high Pass and notch (checked in the PM code)
 double FIRCoeff[MAX_NUMTAPS];        // FIR filter coefficients.  MAX_NUMTAPS = 256
 double OmegaC = 0.2;                 // 0.0 < OmegaC < 1.0
 double BW = 0.1;                     // 0.0 < BandWidth < 1.0
 TFIRPassTypes PassType = firLPF;     // firLPF, firHPF, firBPF, firNOTCH, firALLPASS  See FIRFilterCode.h
 TWindowType WindowType = wtKAISER;   // wtNONE, wtKAISER, wtSINC, and others.   See the FFT header file.
 double WinBeta = 4.0;                // 0 <= WinBeta <= 10.0  This controls the Kaiser and Sinc windows.
 double ParksWidth = 0.15;            // 0.01 <= ParksWidth <= 0.3 The transition bandwidth.
                                      // 0.01 <= ParksWidth <= 0.15 if BPF or NOTCH or if NumTaps > 70


 // Use either RectWinFIR or NewParksMcClellan to calculate the FIR Coefficients.
 RectWinFIR(FIRCoeff, NumTaps, PassType, OmegaC, BW);
 FIRFilterWindow(FIRCoeff, NumTaps, WindowType, WinBeta); // Use a window with RectWinFIR.
 //NewParksMcClellan(FIRCoeff, NumTaps, PassType, OmegaC, BW, ParksWidth); // This doesn't require a window, but one may be used.

 if(FreqCorrection && PassType != firALLPASS)
  {
   double OrigOmega = OmegaC;
   double OrigBW = BW;

   // This function corrects OmegaC for LPF and HPF. It corrects BW for BPF and Notch.
   FIRFreqError(FIRCoeff, NumTaps, PassType, &OmegaC, &BW);

   // Recalculate the filter with the corrected OmegaC and BW values.
   RectWinFIR(FIRCoeff, NumTaps, PassType, OmegaC, BW);
   FIRFilterWindow(FIRCoeff, NumTaps, WindowType, WinBeta);  // Use a window with RectWinFIR.
   //NewParksMcClellan(FIRCoeff, NumTaps, PassType, OmegaC, BW, ParksWidth); // This doesn't require a window, but one may be used.

   OmegaC = OrigOmega; // Restore these in case they are needed.
   BW = OrigBW;
  }

 // We can use AdjustDelay to make fractional delay adjustments to the filter. Typically, the
 // delay can be adjusted by +/- NumTaps/20 without affecting the filter's performance significantly.
 // This is done to align signals and is done as the last step (after the application of the window).
 // AdjustDelay(FIRCoeff, NumTaps, 0.5);

 // Calculate the frequency response of the filter with an FFT.
 for(k=0; k<NUM_SAMPLES; k++)RealHofZ[k] = ImagHofZ[k] = 0.0;             // Init the arrays
 for(k=0; k<NumTaps; k++)RealHofZ[k] = FIRCoeff[k] * (double)NUM_SAMPLES; // Need to do this scaling to account for the 1/N scaling done by the forward FFT.
 FFT(RealHofZ, ImagHofZ, NUM_SAMPLES, FORWARD);                           // The FFT's results are returned in input arrays, RealHofZ and ImagHofZ.


 //Print the FIR coefficients to a text file.
 FILE *OutputFile;
 OutputFile = fopen("FIR Filter Coeff.txt","w");
 for(int j=0; j<NumTaps; j++)
  {
   fprintf(OutputFile,"\n %9.9f ", FIRCoeff[j]);
  }
 fclose(OutputFile);
}
