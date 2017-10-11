#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QWidget>
#include <vector>
#include "UserInfo.h"
#include "common.h"
using namespace std;

namespace Ui {
class editwindow;
}

class editwindow : public QWidget
{
    Q_OBJECT

public:
    explicit editwindow(QWidget *parent = 0,
                        vector<double>DataSet={0.0},
                        vector<double>FreqSet={0.0});
    ~editwindow();

private slots:
    double SlotCaculateMean();
    double SlotCaculateRMS();
    double SlotCaculateVAR();
    double SlotCaculateStdDev();
    double SlotCaculateFreqMean();
    double SlotCaculateFreqPeak();
    double SlotCaculateSigEntropy();
    double SlotCaculateSigPower();
    void SlotSaveFeatures();
    void SlotCalulateAll();
    void SlotClose();

private:
    Features features;
    vector<Features> VectorFeatures;

private:
    Ui::editwindow *ui;
    UserInfo *user;
    vector<double>DataSet;
    vector<double>FreqSet;

private:
    void GetFormulaMap();
    void GetFormerResult();
    void SaveFeatures();
};

#endif // EDITWINDOW_H
