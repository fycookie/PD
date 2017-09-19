#ifndef FIRFILTER_H
#define FIRFILTER_H

class FIRfilter
{
public:
    FIRfilter();
    ~FIRfilter() {}

public:
    void FIRCall(void);

//private:
//    void RectWinFIR(double *FirCoeff, int NumTaps,
//             TFIRPassTypes PassType, double OmegaC, double BW);
//    void FIRFilterWindow(double *FIRCoeff, int N,
//             TWindowType WindowType, double Beta);
};

#endif // FIRFILTER_H
