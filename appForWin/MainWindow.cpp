#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include "qcustomplot.h"
#include <QFileInfo>
#include <QFileDialog>
#include <fstream>
#include "constants.h"
#include <fstream>
#include "FFTCode.h"
#include "FIRFilterCode.h"
#include "math.h"
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMaximumSize(750,500);
    this->setMinimumSize(600,450);
    ui->rawDataPlotBtn->setEnabled(false);
    ui->widgetplotX->setVisible(false);
    ui->widgetplotY->setVisible(false);
    ui->widgetplotZ->setVisible(false);
    ui->widgetplotO->setVisible(false);
    ui->widgetPlotZoom->setVisible(false);
    ui->filterDataBtn->setEnabled(false);
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(fileOpen()));
    connect(ui->actionClose,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->rawDataPlotBtn,SIGNAL(clicked()),this,SLOT(drawRawDataSlot()));
    connect(ui->filterDataBtn,SIGNAL(clicked()),this,SLOT(drawFilterData()));
//    connect(ui->widgetplotY,SIGNAL(mouseMove(QMouseEvent*)),this,
//            SLOT(mouseMove(QMouseEvent*)));

    rubberBand = new QRubberBand(QRubberBand::Rectangle, ui->widgetPlotZoom);
    connect(ui->widgetPlotZoom, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
    connect(ui->widgetPlotZoom, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    connect(ui->widgetPlotZoom, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseRelease(QMouseEvent*)));
    connect(ui->resetBtn, SIGNAL(clicked()), this, SLOT(slotBtn()));

    connect(ui->xAxisBtn,SIGNAL(clicked()),this,SLOT(drawWithZoom(xAxisRawData)));
    connect(ui->yAxisBtn,SIGNAL(clicked()),this,SLOT(drawWithZoom(yAxisRawData)));
    connect(ui->yAxisBtn,SIGNAL(clicked()),this,SLOT(drawWithZoom(zAxisRawData)));
    connect(ui->yAxisBtn,SIGNAL(clicked()),this,SLOT(drawWithZoom(oAxisRawData)));
}

void MainWindow::mouseMove(QMouseEvent *mevent)
{
    if(rubberBand->isVisible())
        rubberBand->setGeometry(QRect(rubberOrigin,mevent->pos()).normalized());
}

void MainWindow::slotBtn()
{
    ui->widgetPlotZoom->rescaleAxes();
    ui->widgetPlotZoom->replot();
}

void MainWindow::mousePress(QMouseEvent *mevent)
{
    if(mevent->button()==Qt::RightButton)
    {
        rubberOrigin=mevent->pos();
        rubberBand->setGeometry(QRect(rubberOrigin,QSize()));
        rubberBand->show();
    }
}

void MainWindow::mouseRelease(QMouseEvent *mevent)
{
    Q_UNUSED(mevent);
    if(rubberBand->isVisible())
    {
        const QRect zoomRect=rubberBand->geometry();
        int xpOne,xpTwo,ypOne,ypTwo;
        zoomRect.getCoords(&xpOne,&ypOne,&xpTwo,&ypTwo);

        double xOne=ui->widgetPlotZoom->xAxis->pixelToCoord(xpOne);
        double xTwo=ui->widgetPlotZoom->xAxis->pixelToCoord(xpTwo);
        double yOne=ui->widgetPlotZoom->yAxis->pixelToCoord(ypTwo);
        double yTwo=ui->widgetPlotZoom->yAxis->pixelToCoord(ypTwo);

        ui->widgetPlotZoom->xAxis->setRange(xOne,xTwo);
        ui->widgetPlotZoom->yAxis->setRange(yOne,yTwo);

        rubberBand->hide();
        ui->widgetPlotZoom->replot();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileOpen()
{
    QString fileFull;
    QFileInfo fileInfo;
    fileFull=QFileDialog::getOpenFileName();
    fileInfo=QFileInfo(fileFull);
    string fileName=fileInfo.fileName().toStdString();
    string fileSuffix=fileInfo.suffix().toStdString();
    string filePath=fileInfo.absoluteFilePath().toStdString();
    if(fileSuffix == "csv")
    {
        int reg = ReadCSV(filePath);
        if(reg >0)
        {
            ui->rawDataPlotBtn->setEnabled(true);
            ui->filterDataBtn->setEnabled(true);
        }
    }
//    else if(fileSuffix == "xlsx")
//    {
//        ReadExcel(filePath);
//    }
//    else if(fileSuffix == "txt")
//    {
//        ReadTxt(filePath);
//    }
    else
    {

    }
}

int MainWindow::ReadCSV(string filePath)
{
    ifstream iFile(filePath);
    if(iFile.is_open())
    {
        while(!iFile.eof())
        {
            iFile.getline(buffer,256);
            int reg=sscanf_s(buffer,"%lf,%lf,%lf,%lf",&coor.t,&coor.x,&coor.y,&coor.z);
            if(reg==4)
            {
                coVector.push_back(coor);
                tVectorRawData.push_back(coor.t);
                xVectorRawData.push_back(coor.x);
                yVectorRawData.push_back(coor.y);
                zVectorRawData.push_back(coor.z);
                Signal.push_back(sqrt(coor.x*coor.x+coor.y*coor.y+coor.z*coor.z));
            }
            else
                break;
        }
        iFile.close();
    }
    else
    {
        qDebug()<<"Cannot open the file!\n";
    }
    return coVector.size();
}

//void MainWindow::mouseMove(QMouseEvent* event)
//{
//    int x_pos=event->pos().x();
//    int y_pos=event->pos().y();

//    // 把鼠标坐标点 转换为 QCustomPlot 内部坐标值 （pixelToCoord 函数）
//    // coordToPixel 函数与之相反 是把内部坐标值 转换为外部坐标点
//    double x_val = ui->widgetplotY->xAxis->pixelToCoord(x_pos);
//    double y_val = ui->widgetplotY->yAxis->pixelToCoord(y_pos);

//    // 然后打印在界面上
//    ui->textEdit->setText(tr("(%1\n  %2\n  ||\n  %3\n  %4)")
//                       .arg(x_pos).arg(y_pos).arg(x_val).arg(y_val));
//}

void MainWindow::drawRawDataSlot()
{
    ui->widgetplotX->setVisible(true);
    ui->widgetplotY->setVisible(true);
    ui->widgetplotZ->setVisible(true);
    ui->widgetplotO->setVisible(true);
    ui->widgetPlotZoom->setVisible(false);

//    QCustomPlot *xPlot=ui->widgetplotX;
//    QCustomPlot *yPlot=ui->widgetplotY;
//    QCustomPlot *zPlot=ui->widgetplotZ;
//    QCustomPlot *oPlot=ui->widgetplotO;
    if(tVectorRawData.size()>0 && xVectorRawData.size()>0)
        DrawData(ui->widgetplotX, tVectorRawData, xVectorRawData);
    if(tVectorRawData.size()>0 && yVectorRawData.size()>0)
        DrawData(ui->widgetplotY, tVectorRawData, yVectorRawData);
    if(tVectorRawData.size()>0 && zVectorRawData.size()>0)
        DrawData(ui->widgetplotZ, tVectorRawData, zVectorRawData);
    if(tVectorRawData.size()>0 && Signal.size()>0)
        DrawData(ui->widgetplotO, tVectorRawData, Signal);
}

void MainWindow::DrawData(QCustomPlot *plot, vector<double> xx, vector<double> yy)
{
    QVector<double> x(10000),y(10000);
    int i=0;
    for(auto item:xx)
    {
        x[i]=item;
        i++;
        if(i>10000)
            break;
    }
    int j=0;
    for(auto item:yy)
    {
        y[j]=item;
        j++;
        if(j>10000)
            break;
    }
    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::blue));
    plot->graph(0)->setData(x,y);
    plot->xAxis->setLabel("t/s");
    plot->yAxis->setLabel("a/mm");
    plot->setBackground(QColor(100,150,50));
    plot->rescaleAxes();
    //pFilter->xAxis->setRange(0,100);
    //pFilter->yAxis->setRange(0,800);
    plot->replot();
    plot->show();
}

//void MainWindow::drawRawData()
//{
//    if(coVector.size()!=0)
//    {
//        ui->widgetplotX->setVisible(true);
//        ui->widgetplotY->setVisible(true);
//        ui->widgetplotZ->setVisible(true);
//        ui->widgetPlotZoom->setVisible(false);
//        QVector<double> t(10000),x(10000),y(10000),z(10000);
//        int i=0;
//        for(auto item:coVector)
//        {
//            t[i]=item.t;
//            x[i]=item.x;
//            y[i]=item.y;
//            z[i]=item.z;
//            i++;
//            if(i>10000)
//                break;
//        }

//        QCustomPlot *pRawDataPlotX=ui->widgetplotX;
//        pRawDataPlotX->addGraph();
//        pRawDataPlotX->graph(0)->setPen(QPen(Qt::red));
//        pRawDataPlotX->graph(0)->setData(t,x);
//        pRawDataPlotX->xAxis->setLabel("t/s");
//        pRawDataPlotX->yAxis->setLabel("a/mm");
//        pRawDataPlotX->setBackground(QColor(100,150,50));
//        pRawDataPlotX->rescaleAxes();
//        pRawDataPlotX->xAxis->setRange(0,100);
//        pRawDataPlotX->yAxis->setRange(-800,800);
//        pRawDataPlotX->axisRect()->setRangeZoom(Qt::Vertical);
//        pRawDataPlotX->replot();
//        pRawDataPlotX->show();

//        QCustomPlot *pRawDataPlotY=ui->widgetplotY;
//        pRawDataPlotY->addGraph();
//        pRawDataPlotY->graph(0)->setPen(QPen(Qt::blue));
//        pRawDataPlotY->graph(0)->setData(t,y);
//        pRawDataPlotY->xAxis->setLabel("t/s");
//        pRawDataPlotY->yAxis->setLabel("a/mm");
//        pRawDataPlotY->setBackground(QColor(100,150,50));
//        pRawDataPlotY->rescaleAxes();
//        pRawDataPlotY->xAxis->setRange(0,100);
//        pRawDataPlotY->yAxis->setRange(-800,800);
//        double dCenter = pRawDataPlotY->xAxis->range().center();
//        pRawDataPlotY->xAxis->scaleRange(2.0,dCenter);
//        pRawDataPlotY->xAxis->scaleRange(0.5,dCenter);
//        pRawDataPlotY->replot();
//        pRawDataPlotY->show();

//        QCustomPlot *pRawDataPlotZ=ui->widgetplotZ;
//        pRawDataPlotZ->addGraph();
//        pRawDataPlotZ->graph(0)->setPen(QPen(Qt::yellow));
//        pRawDataPlotZ->graph(0)->setData(t,z);
//        pRawDataPlotZ->xAxis->setLabel("t/s");
//        pRawDataPlotZ->yAxis->setLabel("a/mm");
//        pRawDataPlotZ->setBackground(QColor(100,150,50));
//        pRawDataPlotZ->rescaleAxes();
//        pRawDataPlotZ->xAxis->setRange(0,100);
//        pRawDataPlotZ->yAxis->setRange(-800,800);
//        pRawDataPlotZ->replot();
//        pRawDataPlotZ->show();

//        QFont xFont=pRawDataPlot->xAxis->labelFont();
//        xFont.setPixelSize(20);
//        pRawDataPlot->xAxis->setLabelFont(xFont);
//        QFont yFont = pRawDataPlot->yAxis->labelFont();
//        yFont.setPixelSize(20);
//        pRawDataPlot->yAxis->setLabelFont(yFont);
//    }
//}

void MainWindow::drawWithZoom(DrawType type)
{
    ui->widgetplotX->setVisible(false);
    ui->widgetplotY->setVisible(false);
    ui->widgetplotZ->setVisible(false);
    ui->widgetplotO->setVisible(false);
    ui->widgetPlotZoom->setVisible(true);
    switch(type)
    {
        case xAxisRawData:
            Zoom(tVectorRawData,xVectorRawData);
            break;
        case yAxisRawData:
            Zoom(tVectorRawData,yVectorRawData);
            break;
        case zAxisRawData:
            Zoom(tVectorRawData,zVectorRawData);
            break;
        case oAxisRawData:
            Zoom(tVectorRawData,Signal);
            break;
        case xAxisFilted:
            Zoom(tVectorRawData,yVectorRawData);
            break;
        case yAxisFilted:
            Zoom(tVectorRawData,zVectorRawData);
            break;
        case zAxisFilted:
            Zoom(tVectorRawData,yVectorRawData);
            break;
        case oAxisFilted:
            Zoom(tVectorRawData,zVectorRawData);
            break;
    }
}

void MainWindow::Zoom(vector<double> xx, vector<double> yy)
{
    QVector<double> x(10000),y(10000);
    int i=0;
    for(auto item:xx)
    {
        x[i]=item;
        i++;
        if(i>10000)
            break;
    }
    int j=0;
    for(auto item:yy)
    {
        y[j]=item;
        j++;
        if(j>10000)
            break;
    }

    QCustomPlot *pZoom=ui->widgetPlotZoom;
    pZoom->addGraph();
    pZoom->graph(0)->setPen(QPen(Qt::blue));
    pZoom->graph(0)->setData(x,y);
    pZoom->xAxis->setLabel("t/s");
    pZoom->yAxis->setLabel("a/mm");
    pZoom->setBackground(QColor(100,150,50));
    pZoom->rescaleAxes();
    //pFilter->xAxis->setRange(0,100);
    //pFilter->yAxis->setRange(0,800);
    pZoom->replot();
    pZoom->show();
}

void MainWindow::drawFilterData()
{
    if(Signal.size()>0)
    {
        ui->widgetplotX->setVisible(true);
        ui->widgetplotY->setVisible(true);
        ui->widgetplotZ->setVisible(true);
        ui->widgetplotO->setVisible(true);
        ui->widgetPlotZoom->setVisible(false);
        FIRCall();

        if(xVectorFilted.size()>0)
        {
            Convolution(xAxisFilted, xVectorFilted);
            DrawData(ui->widgetplotX, tVectorRawData, xVectorFilted);
        }
        if(yVectorFilted.size()>0)
        {
            Convolution(yAxisFilted, yVectorFilted);
            DrawData(ui->widgetplotY, tVectorRawData, yVectorFilted);
        }
        if(zVectorFilted.size()>0)
        {
            Convolution(zAxisFilted, zVectorFilted);
            DrawData(ui->widgetplotZ, tVectorRawData, zVectorFilted);
        }
        if(FirResult.size()>0)
        {
            Convolution(oAxisFilted, FirResult);
            DrawData(ui->widgetplotO, tVectorRawData, FirResult);
        }
    }
}

void MainWindow::FIRCall()
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
// RectWinFIR(FIRCoeff, NumTaps, PassType, OmegaC, BW);
// FIRFilterWindow(FIRCoeff, NumTaps, WindowType, WinBeta); // Use a window with RectWinFIR.
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
// FILE *OutputFile;
// OutputFile = fopen("FIR Filter Coeff.txt","w");
 for(int j=0; j<NumTaps; j++)
  {
     FirCoeff.push_back(FIRCoeff[j]);
  }
// fclose(OutputFile);
}

void MainWindow::Convolution(DrawType type, vector<double> RawData)
{
    int mm = FirCoeff.size();
    int nn = RawData.size();
    float *xx = new float[mm+nn-1];     // do convolution
    for (int i = 0; i < mm+nn-1; i++)
    {
        xx[i] = 0.0;
        for (int j = 0; j < mm; j++)
        {
            if (i-j > 0 && i-j < nn)
                xx[i] += FirCoeff[j] * RawData[i-j];
        }
    }     // set value to the output array

    switch (type) {
    case xAxisFilted:
        for (int i = 0; i < mm; i++)
            xVectorFilted.push_back(xx[i + (nn-1) / 2]);
        break;
    case yAxisFilted:
        for (int i = 0; i < mm; i++)
            yVectorFilted.push_back(xx[i + (nn-1) / 2]);
        break;
    case zAxisFilted:
        for (int i = 0; i < mm; i++)
            zVectorFilted.push_back(xx[i + (nn-1) / 2]);
        break;
    case oAxisFilted:
        for (int i = 0; i < mm; i++)
            FirResult.push_back(xx[i + (nn-1) / 2]);
        break;
    default:
        break;
    }

    delete[] xx;
}


//void convolution(double *input1, double *input2, double *output, int mm, int nn)
// {
//     float *xx = new float[mm+nn-1];     // do convolution
//     for (int i = 0; i < mm+nn-1; i++)
//     {
//         xx[i] = 0.0;
//         for (int j = 0; j < mm; j++)
//         {
//             if (i-j > 0 && i-j < nn)
//                 xx[i] += input1[j] * input2[i-j];
//         }
//     }     // set value to the output array
//     for (int i = 0; i < mm; i++)
//         output[i] = xx[i + (nn-1) / 2];
//     delete[] xx;
// }
