#include "editwindow.h"
#include "ui_editwindow.h"
#include <QPixmap>
#include <vector>
#include "math.h"
#include "userinfo.h"
#include <QMessageBox>
using namespace std;

editwindow::editwindow(QWidget *parent,
                       vector<double> data,
                       vector<double>freq):
    QWidget(parent),
    ui(new Ui::editwindow)
{
    ui->setupUi(this);
    this->DataSet.assign(data.begin(),data.end());
    this->FreqSet.assign(freq.begin(),freq.end());
    GetFormulaMap();
    GetFormerResult();

    connect(ui->btnMEAN,SIGNAL(clicked(bool)),
            this,SLOT(SlotCaculateMean()));
    connect(ui->btnRMS,SIGNAL(clicked(bool)),
            this,SLOT(SlotCaculateRMS()));
    connect(ui->btnVAR,SIGNAL(clicked(bool)),
            this,SLOT(SlotCaculateVAR()));
    connect(ui->btnStdDev,SIGNAL(clicked(bool)),
            this,SLOT(SlotCaculateStdDev()));
    connect(ui->btnFreqMean,SIGNAL(clicked(bool)),
            this,SLOT(SlotCaculateFreqMean()));
    connect(ui->btnFreqPeak,SIGNAL(clicked(bool)),
            this,SLOT(SlotCaculateFreqPeak()));
    connect(ui->btnSigEntropy,SIGNAL(clicked(bool)),
            this,SLOT(SlotCaculateSigEntropy()));
    connect(ui->btnSigPower,SIGNAL(clicked(bool)),
            this,SLOT(SlotCaculateSigPower()));
    connect(ui->btnSaveFeatures,SIGNAL(clicked(bool)),
            this,SLOT(SlotSaveFeatures()));
    connect(ui->btnCalculate,SIGNAL(clicked(bool)),
            this,SLOT(SlotCalulateAll()));
    connect(ui->btnClose,SIGNAL(clicked(bool)),
            this,SLOT(SlotClose()));
}

editwindow::~editwindow()
{
    delete ui;
}

void editwindow::GetFormulaMap()
{
    QPixmap mean_formular_map("./icon/mean_formula.png");
    mean_formular_map=mean_formular_map.scaled(
                ui->labelMeanFormula->width(),
                ui->labelMeanFormula->height());
    ui->labelMeanFormula->setPixmap(mean_formular_map);

    QPixmap rms_formula_map("./icon/rms_formula.png");
    rms_formula_map=rms_formula_map.scaled(
                ui->labelRmsFormula->width(),
                ui->labelRmsFormula->height());
    ui->labelRmsFormula->setPixmap(rms_formula_map);

    QPixmap var_formula_map("./icon/var_formula.png");
    var_formula_map=var_formula_map.scaled(
                ui->labelVarFormula->width(),
                ui->labelVarFormula->height());
    ui->labelVarFormula->setPixmap(var_formula_map);

    QPixmap standard_formula_map("./icon/standard_formula.png");
    standard_formula_map=standard_formula_map.scaled(
                ui->labelStdDevFormula->width(),
                ui->labelStdDevFormula->height());
    ui->labelStdDevFormula->setPixmap(standard_formula_map);
}

void editwindow::SlotCalulateAll()
{
    SlotCaculateMean();
    SlotCaculateRMS();
    SlotCaculateVAR();
    SlotCaculateStdDev();
    SlotCaculateFreqMean();
    SlotCaculateFreqPeak();
    SlotCaculateSigEntropy();
    SlotCaculateSigPower();
}

void editwindow::SlotClose()
{
    QMessageBox::StandardButton rb = QMessageBox::question(NULL,
        "Warning","Leaving?",QMessageBox::Yes|QMessageBox::No,
         QMessageBox::Yes);
    if(rb==QMessageBox::Yes)
        this->close();
}

void editwindow::SlotSaveFeatures()
{
    if(ui->labelMeanResult->text().toDouble()==features.MEAN &&
       ui->labelRmsResult->text().toDouble()==features.RMS &&
       ui->labelVarResult->text().toDouble()==features.VAR &&
       ui->labelStdDevResult->text().toDouble()==features.StdDev &&
       ui->labelResultFreqMean->text().toDouble()==features.FreqMean &&
       ui->labelResultFreqPeak->text().toDouble()==features.FreqPeak &&
       ui->labelResultSigEntropy->text().toDouble()==features.SigEntropy &&
       ui->labelResultSigPower->text().toDouble()==features.SigPower)
        return;

    SaveFeatures();
}

void editwindow::SaveFeatures()
{
    user->AddFeatures(&features);
}

void editwindow::GetFormerResult()
{
    user->LoadFeatures(&VectorFeatures);
    if(VectorFeatures.size()>0)
    {
        for(Features item:VectorFeatures)
        {
            ui->textEditTimeDomain->append(QString("'%1','%2',"
                                           "'%3','%4','%5'\n")
                            .arg(item.datetime)
                            .arg(item.MEAN)
                            .arg(item.RMS)
                            .arg(item.VAR)
                            .arg(item.StdDev));

            ui->textEditFreqDomain->append(QString("'%1','%2',"
                                           "'%3','%4','%5'\n")
                            .arg(item.datetime)
                            .arg(item.FreqMean)
                            .arg(item.FreqPeak)
                            .arg(item.SigPower)
                            .arg(item.SigEntropy));
        }
    }
}

double editwindow::SlotCaculateMean()
{
    double result=0.0;
    if(DataSet.size()<1)
        return result;
    else
        for(auto item:DataSet)
            result += item;
    result /=DataSet.size();

    features.MEAN=result;
    ui->labelMeanResult->setText(QString::number(result));
    return result;
}

double editwindow::SlotCaculateRMS()
{
    double result=0.0;
    if(DataSet.size()<1)
        return result;

    for(auto item:DataSet)
        result += item*item;
    result /=DataSet.size();
    result=sqrt(result);

    features.RMS=result;
    ui->labelRmsResult->setText(QString::number(result));
    return result;
}

double editwindow::SlotCaculateVAR()
{
    double result=0.0;
    if(DataSet.size()<1)
        return result;
    if(features.MEAN == 0.0)
        if(SlotCaculateMean()==0.0)
            return result;

    for(auto item:DataSet)
        result += (item-features.MEAN)*(item-features.MEAN);
    result /=DataSet.size();

    features.VAR=result;
    ui->labelVarResult->setText(QString::number(result));
    return result;
}

double editwindow::SlotCaculateStdDev()
{
    double result=0.0;
    if(DataSet.size()<1)
        return result;
    if(features.VAR == 0.0)
        if(SlotCaculateVAR()==0.0)
            return result;

    result /=sqrt(features.VAR);
    features.StdDev=result;
    ui->labelStdDevResult->setText(QString::number(result));
    return result;
}

double editwindow::SlotCaculateFreqMean()
{
    double result=0.0;
    if(FreqSet.size()<1)
        return result;
    else
        for(auto item:FreqSet)
            result += item;
    result /=FreqSet.size();

    features.FreqMean=result;
    ui->labelResultFreqMean->setText
            (QString::number(result));
    return result;
}

double editwindow::SlotCaculateFreqPeak()
{
    double result=0.0;
    if(FreqSet.size()<1)
        return result;
    else
        for(auto item:FreqSet)
            result =result>item?result:item;

    features.FreqPeak=result;
    ui->labelResultFreqPeak->setText
            (QString::number(result));
    return result;
}

//需要完善
double editwindow::SlotCaculateSigPower()
{
    double result=0.0;
    ui->labelResultSigPower->setText
            (QString::number(result));
    return result;
}
//需要完善
double editwindow::SlotCaculateSigEntropy()
{
    double result=0.0;
    ui->labelResultSigEntropy->setText
            (QString::number(result));
    return result;
}
