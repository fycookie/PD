#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <vector>
using namespace std;

struct Features{
    QString datetime="";
    double MEAN=0.0;
    double RMS=0.0;
    double VAR=0.0;
    double StdDev=0.0;
    double FreqMean=0.0;
    double FreqPeak=0.0;
    double SigPower=0.0;
    double SigEntropy=0.0;
};

struct sample{
    vector<double> features;
    int label=0;
    double distance=0.0;
    int result=0;
};

#endif // COMMON_H
