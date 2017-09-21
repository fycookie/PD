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
#include <QButtonGroup>
#include "cfft.h"
#include "complex.h"
#include "tryfft.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMaximumSize(750,500);
    this->setMinimumSize(600,450);
    ui->widgetplotX->setVisible(false);
    ui->widgetplotY->setVisible(false);
    ui->widgetplotZ->setVisible(false);
    ui->widgetplotO->setVisible(false);
    ui->widgetPlotZoom->setVisible(false);

    plotGroup=new QButtonGroup(this);
    plotGroup->addButton(ui->rdbtnRawData,0);
    plotGroup->addButton(ui->rdbtnFiltData,1);
    plotGroup->addButton(ui->rdbtnFFT,2);
    ui->rdbtnRawData->setEnabled(false);
    ui->rdbtnFiltData->setEnabled(false);
    ui->rdbtnFFT->setEnabled(false);

//    axisGroup=new QButtonGroup(this);
//    axisGroup->addButton((ui->xAxisBtn,0));
//    axisGroup->addButton((ui->yAxisBtn,1));
//    axisGroup->addButton((ui->zAxisBtn,2));
//    axisGroup->addButton((ui->oAxisBtn,3));

    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(fileOpen()));
    connect(ui->actionClose,SIGNAL(triggered()),this,SLOT(close()));
    //connect(plotGroup,SIGNAL(buttonClicked(int)),this,SLOT(rdbtnSlot(int)));
    connect(ui->rdbtnRawData,SIGNAL(clicked()),this,SLOT(rdbtnSlot()));
    connect(ui->rdbtnFiltData,SIGNAL(clicked()),this,SLOT(rdbtnSlot()));
    connect(ui->rdbtnFFT,SIGNAL(clicked(bool)),this,SLOT(rdbtnSlot()));

    connect(ui->xAxisBtn,SIGNAL(clicked()),this,SLOT(axisX()));
    connect(ui->yAxisBtn,SIGNAL(clicked()),this,SLOT(axisY()));
    connect(ui->zAxisBtn,SIGNAL(clicked()),this,SLOT(axisZ()));
    connect(ui->oAxisBtn,SIGNAL(clicked()),this,SLOT(axisO()));

//    connect(ui->filterDataBtn,SIGNAL(clicked()),this,SLOT(drawFilterData()));
//    connect(ui->widgetplotY,SIGNAL(mouseMove(QMouseEvent*)),this,
//            SLOT(mouseMove(QMouseEvent*)));

    rubberBand = new QRubberBand(QRubberBand::Rectangle, ui->widgetPlotZoom);
    connect(ui->widgetPlotZoom, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
    connect(ui->widgetPlotZoom, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
    connect(ui->widgetPlotZoom, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseRelease(QMouseEvent*)));
    connect(ui->resetBtn, SIGNAL(clicked()), this, SLOT(slotBtn()));
}

void MainWindow::rdbtnSlot()
{
    if(plotGroup->checkedId()==0)
        drawRawData();
    else if(plotGroup->checkedId()==1)
        drawFiltedData();
    else if(plotGroup->checkedId()==2)
        drawFFT();
}

void MainWindow::axisX()
{
    if(plotGroup->checkedId()==0)
        drawWithZoom(xAxisRawData);
    else if(plotGroup->checkedId()==1)
        drawWithZoom(xAxisFilted);
    else if(plotGroup->checkedId()==2)
        drawWithZoom(xAxisFFT);
}
void MainWindow::axisY()
{
    if(plotGroup->checkedId()==0)
        drawWithZoom(yAxisRawData);
    else if(plotGroup->checkedId()==1)
        drawWithZoom(yAxisFilted);
    else if(plotGroup->checkedId()==2)
        drawWithZoom(yAxisFFT);
}
void MainWindow::axisZ()
{
    if(plotGroup->checkedId()==0)
        drawWithZoom(zAxisRawData);
    else if(plotGroup->checkedId()==1)
        drawWithZoom(zAxisFilted);
    else if(plotGroup->checkedId()==1)
        drawWithZoom(zAxisFFT);
}
void MainWindow::axisO()
{
    if(plotGroup->checkedId()==0)
        drawWithZoom(oAxisRawData);
    else if(plotGroup->checkedId()==1)
        drawWithZoom(oAxisFilted);
    else if(plotGroup->checkedId()==1)
        drawWithZoom(oAxisFFT);
}

//void MainWindow::axisSelect(AxisType type)
//{
//    if(plotGroup->checkedId()==0)
//    {
//        switch (type) {
//        case xAxis:
//            drawWithZoom(xAxisRawData);
//            break;
//        case yAxis:
//            drawWithZoom(yAxisRawData);
//            break;
//        case zAxis:
//            drawWithZoom(zAxisRawData);
//            break;
//        case oAxis:
//            drawWithZoom(oAxisRawData);
//            break;
//        default:
//            break;
//        }
//    }
//    else if(plotGroup->checkedId()==1)
//    {
//        switch (type) {
//        case xAxis:
//            drawWithZoom(xAxisFilted);
//            break;
//        case yAxis:
//            drawWithZoom(yAxisFilted);
//            break;
//        case zAxis:
//            drawWithZoom(zAxisFilted);
//            break;
//        case oAxis:
//            drawWithZoom(oAxisFilted);
//            break;
//        default:
//            break;
//        }
//    }
//}

//void MainWindow::rdbtnSlot(int id)
//{
//    if(id == 0)
//    {
//        //drawRawData();
//        connect(ui->xAxisBtn,SIGNAL(clicked()),this,SLOT(drawWithZoom(xAxisRawData)));
//        connect(ui->yAxisBtn,SIGNAL(clicked()),this,SLOT(drawWithZoom(yAxisRawData)));
//        connect(ui->zAxisBtn,SIGNAL(clicked()),this,SLOT(drawWithZoom(zAxisRawData)));
//        connect(ui->oAxisBtn,SIGNAL(clicked()),this,SLOT(drawWithZoom(oAxisRawData)));
//    }
//    else if(id == 1)
//    {
//        //drawFiltedData();
//        connect(ui->xAxisBtn,SIGNAL(clicked()),this,SLOT(drawWithZoom(xAxisFilted)));
//        connect(ui->yAxisBtn,SIGNAL(clicked()),this,SLOT(drawWithZoom(yAxisFilted)));
//        connect(ui->zAxisBtn,SIGNAL(clicked()),this,SLOT(drawWithZoom(zAxisFilted)));
//        connect(ui->oAxisBtn,SIGNAL(clicked()),this,SLOT(drawWithZoom(oAxisFilted)));
//    }
//}

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
            ui->rdbtnRawData->setEnabled(true);
            ui->rdbtnFiltData->setEnabled(true);
            ui->rdbtnFFT->setEnabled(true);
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

void MainWindow::drawRawData()
{
    ui->widgetplotX->setVisible(false);
    ui->widgetplotY->setVisible(false);
    ui->widgetplotZ->setVisible(false);
    ui->widgetplotO->setVisible(false);
    ui->widgetPlotZoom->setVisible(false);

    if(tVectorRawData.size()>0 && xVectorRawData.size()>0)
        DrawData(ui->widgetplotX, tVectorRawData, xVectorRawData);
    if(tVectorRawData.size()>0 && yVectorRawData.size()>0)
        DrawData(ui->widgetplotY, tVectorRawData, yVectorRawData);
    if(tVectorRawData.size()>0 && zVectorRawData.size()>0)
        DrawData(ui->widgetplotZ, tVectorRawData, zVectorRawData);
    if(tVectorRawData.size()>0 && Signal.size()>0)
        DrawData(ui->widgetplotO, tVectorRawData, Signal);
}

void MainWindow::DrawFFTAxis(QCustomPlot *plot, vector<double> xx, vector<double> yy)
{
//    ui->widgetplotX->removeGraph(0);
//    ui->widgetplotY->removeGraph(0);
//    ui->widgetplotZ->removeGraph(0);
//    ui->widgetplotO->removeGraph(0);
    ui->widgetplotX->setVisible(true);
    ui->widgetplotY->setVisible(true);
    ui->widgetplotZ->setVisible(true);
    ui->widgetplotO->setVisible(true);
    ui->widgetPlotZoom->setVisible(false);
    plot->setVisible(false);
    QVector<double> x(SAMPLE),y(SAMPLE);
    for(int i=0;i<SAMPLE;i++)
    {
        x[i]=xx[i];
        y[i]=yy[i];
    }
    QMargins margins(10,5,5,5);
    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::yellow));
    plot->xAxis->setLabel("fs/Hz");
    plot->yAxis->setLabel("a/mm^2");
    plot->axisRect()->setMargins(margins);
    plot->setBackground(QColor(100,150,50));
    plot->graph(0)->setData(x,y);

//    QCPAxisRect *axisRect=new QCPAxisRect(plot);
//    plot->plotLayout()->addElement(axisRect);
//    axisRect->axis(QCPAxis::atBottom)->setLayer("axes");
//    axisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
//    plot->plotLayout()->setRowSpacing(5);
//    connect(axisRect->axis(QCPAxis::atBottom),SIGNAL(rangeChanged(QCPRange)),
//            plot->xAxis,SLOT(setRange(QCPRange)));

    plot->rescaleAxes(true);
    plot->replot();
}

void MainWindow::DrawData(QCustomPlot *plot, vector<double> xx, vector<double> yy)
{
    ui->widgetplotX->setVisible(true);
    ui->widgetplotY->setVisible(true);
    ui->widgetplotZ->setVisible(true);
    ui->widgetplotO->setVisible(true);
    ui->widgetPlotZoom->setVisible(false);

    plot->setVisible(false);
    QVector<double> x(15000),y(15000);
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
//        if(j==9550)
//        {
//            qDebug()<<"haha";
//        }
    }
    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::blue));
    plot->graph(0)->setData(x,y);
    plot->xAxis->setLabel("t/s");
    plot->yAxis->setLabel("a/mm");
    plot->setBackground(QColor(100,150,50));
    plot->rescaleAxes();
    plot->setEnabled(true);
    plot->replot();
    plot->show();
}

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
            Zoom(tVectorRawData,xVectorFilted);
            break;
        case yAxisFilted:
            Zoom(tVectorRawData,yVectorFilted);
            break;
        case zAxisFilted:
            Zoom(tVectorRawData,zVectorFilted);
            break;
        case oAxisFilted:
            Zoom(tVectorRawData,FirResult);
            break;
        case xAxisFFT:
            Zoom(xxFFT,xVectorFFT);
            break;
        case yAxisFFT:
            Zoom(xxFFT,yVectorFFT);
            break;
        case zAxisFFT:
            Zoom(xxFFT,zVectorFFT);
            break;
        case oAxisFFT:
            Zoom(xxFFT,oVectorFFT);
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
    pZoom->xAxis->setRange(0,50);
    pZoom->yAxis->setRange(0,800);
    pZoom->replot();
    pZoom->show();
}

void MainWindow::drawFiltedData()
{
    ui->widgetplotX->setVisible(false);
    ui->widgetplotY->setVisible(false);
    ui->widgetplotZ->setVisible(false);
    ui->widgetplotO->setVisible(false);
    ui->widgetPlotZoom->setVisible(false);

    if(FirCoeff.size()==0)
    {
        FIRCall();//防止FirCoeff被重复幅值
    }

    if(Signal.size()>0)
    {
        if(FirResult.size()==0)
        {
//            xVectorFilted.assign(xVectorRawData.begin(),xVectorRawData.end());
//            yVectorFilted.assign(yVectorRawData.begin(),yVectorRawData.end());
//            zVectorFilted.assign(zVectorRawData.begin(),zVectorRawData.end());
//            FirResult.assign(Signal.begin(),Signal.end());
//            Convolution(xAxisFilted, xVectorRawData);
//            Convolution(yAxisFilted, yVectorRawData);
//            Convolution(zAxisFilted, zVectorRawData);
//            Convolution(oAxisFilted, Signal);
            Convolution();
        }

        if(xVectorFilted.size()>0)
        {
            DrawData(ui->widgetplotX, tVectorRawData, xVectorFilted);
        }
        if(yVectorFilted.size()>0)
        {
            DrawData(ui->widgetplotY, tVectorRawData, yVectorFilted);
        }
        if(zVectorFilted.size()>0)
        {
            DrawData(ui->widgetplotZ, tVectorRawData, zVectorFilted);
        }
        if(FirResult.size()>0)
        {
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
 double OmegaC = 0.1;                 // 0.0 < OmegaC < 1.0
 double BW = 0.2;                     // 0.0 < BandWidth < 1.0
 TFIRPassTypes PassType = firLPF;     // firLPF, firHPF, firBPF, firNOTCH, firALLPASS  See FIRFilterCode.h
 TWindowType WindowType = wtKAISER;   // wtNONE, wtKAISER, wtSINC, and others.   See the FFT header file.
 double WinBeta = 5.65;                // 0 <= WinBeta <= 10.0  This controls the Kaiser and Sinc windows.
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

 //FFT(RealHofZ, ImagHofZ, NUM_SAMPLES, FORWARD);                           // The FFT's results are returned in input arrays, RealHofZ and ImagHofZ.


 //Print the FIR coefficients to a text file.
// FILE *OutputFile;
// OutputFile = fopen("FIR Filter Coeff.txt","w");
 for(int j=0; j<NumTaps; j++)
  {
     FirCoeff.push_back(FIRCoeff[j]);
  }
// fclose(OutputFile);
}

void MainWindow::Convolution()
{
    int firLen = FirCoeff.size();

    //for x;
    int sigXLen = xVectorRawData.size();
    double ResultX[firLen+sigXLen-1];     // do convolution
    for (int i = 0; i < firLen+sigXLen-1; i++)
    {
        double min,max;

        ResultX[i] = 0.0;
        min=(i>=firLen-1) ? i-(firLen-1):0;
        max=(i<sigXLen-1) ? i:sigXLen-1;

        for(int j=min;j<=max;j++)
        {
            ResultX[i]+=FirCoeff[j] * xVectorRawData[i-j];
        }
    }
    for (int i = 0; i < sigXLen; i++)
        xVectorFilted.push_back(ResultX[i]);

    //for y;
    int sigYLen = yVectorRawData.size();
    double ResultY[firLen+sigYLen-1];     // do convolution
    for (int i = 0; i < firLen+sigYLen-1; i++)
    {
        double min,max;

        ResultY[i] = 0.0;
        min=(i>=firLen-1) ? i-(firLen-1):0;
        max=(i<sigYLen-1) ? i:sigYLen-1;

        for(int j=min;j<=max;j++)
        {
            ResultY[i]+=FirCoeff[j] * yVectorRawData[i-j];
        }
    }
    for (int i = 0; i < sigYLen; i++)
        yVectorFilted.push_back(ResultY[i]);

    //for z;
    int sigZLen = zVectorRawData.size();
    double ResultZ[firLen+sigZLen-1];     // do convolution
    for (int i = 0; i < firLen+sigZLen-1; i++)
    {
        double min,max;

        ResultZ[i] = 0.0;
        min=(i>=firLen-1) ? i-(firLen-1):0;
        max=(i<sigZLen-1) ? i:sigZLen-1;

        for(int j=min;j<=max;j++)
        {
            ResultZ[i]+=FirCoeff[j] * zVectorRawData[i-j];
        }
    }
    for (int i = 0; i < sigZLen; i++)
        zVectorFilted.push_back(ResultZ[i]);

    //for o;
    int sigOLen = Signal.size();
    double ResultO[firLen+sigOLen-1];     // do convolution
    for (int i = 0; i < firLen+sigOLen-1; i++)
    {
        double min,max;

        ResultO[i] = 0.0;
        min=(i>=firLen-1) ? i-(firLen-1):0;
        max=(i<sigOLen-1) ? i:sigOLen-1;

        for(int j=min;j<=max;j++)
        {
            ResultO[i]+=FirCoeff[j] * Signal[i-j];
        }
    }
    for (int i = 0; i < sigOLen; i++)
        FirResult.push_back(ResultO[i]);
}

void MainWindow::drawFFT()
{
    if(oVectorFFT.size()<1)
    {
        xVectorFFT.assign(xVectorRawData.begin(),
                          xVectorRawData.end());
        yVectorFFT.assign(yVectorRawData.begin(),
                          yVectorRawData.end());
        zVectorFFT.assign(zVectorRawData.begin(),
                          zVectorRawData.end());
        oVectorFFT.assign(Signal.begin(),
                          Signal.end());

        FFTData(xVectorFFT);
        FFTData(yVectorFFT);
        FFTData(zVectorFFT);
        FFTData(oVectorFFT);

        for(int i=0;i<SAMPLE;i++)
            xxFFT.push_back(100*i/SAMPLE);
    }
    DrawFFTAxis(ui->widgetplotX,xxFFT,xVectorFFT);
    DrawFFTAxis(ui->widgetplotY,xxFFT,yVectorFFT);
    DrawFFTAxis(ui->widgetplotZ,xxFFT,zVectorFFT);
    DrawFFTAxis(ui->widgetplotO,xxFFT,oVectorFFT);
}

void MainWindow::FFTData(vector<double> &DataVector)
{
    int SIZE=DataVector.size();
    Complex xx[SIZE];
    Complex yy[SAMPLE];
    for(int i=0;i<SIZE;i++)
    {
        xx[i].Update(DataVector[i],0);
    }
    for(int i=0;i<SAMPLE;i++)
    {
        yy[i].Update(0,0);
    }
    FFT(xx,yy,SAMPLE);
    for(int i=0;i<SIZE;i++)
        DataVector[i]=yy[i].Abs();
}


//    int SIZE=DataVector.size();
//    double DataReal[SIZE];
//    double DataImage[SIZE];
//    for(int i=0;i<SIZE;i++)
//    {
//        DataReal[i]=DataVector[i];
//        DataImage[i]=0;
//    }
//    tryFFT(DataReal,DataImage,SIZE,SAMPLE);
//    for(int i=0;i<SIZE;i++)
//        DataVector[i]=sqrt(DataReal[i]*DataReal[i]+
//                           DataImage[i]*DataImage[i]);

//    double x[16],y[16]={0};
//    x[0]=0.5751;
//    x[1]=0.4514;
//    x[2]=0.0439;
//    x[3]=0.0272;
//    x[4]=0.3127;
//    x[5]=0.0129;
//    x[6]=0.3840;
//    x[7]=0.6831;
//    x[8]=0.0928;
//    x[9]=0.0353;
//    x[10]=0.6124;
//    x[11]=0.6085;
//    x[12]=0.0158;
//    x[13]=0.0164;
//    x[14]=0.1901;
//    x[15]=0.5869;
//    tryFFT(x,y,16,16);

//        Complex xx[16],yy[16];
//        xx[0].Update(0.5751,0);
//        xx[1].Update(0.4514,0);
//        xx[2].Update(0.0439,0);
//        xx[3].Update(0.0272,0);
//        xx[4].Update(0.3127,0);
//        xx[5].Update(0.0129,0);
//        xx[6].Update(0.3840,0);
//        xx[7].Update(0.6831,0);
//        xx[8].Update(0.0928,0);;
//        xx[9].Update(0.0353,0);
//        xx[10].Update(0.6124,0);
//        xx[11].Update(0.6085,0);
//        xx[12].Update(0.0158,0);
//        xx[13].Update(0.0164,0);
//        xx[14].Update(0.1901,0);
//        xx[15].Update(0.5869,0);
//        FFT(xx,yy,16);

//            qDebug()<<"hihi\n";
//}
//    double xx[16],yy[16];int m=16;
//    xx[0]=0.5751;
//    xx[1]=0.4514;
//    xx[2]=0.0439;
//    xx[3]=0.0272;
//    xx[4]=0.3127;
//    xx[5]=0.0129;
//    xx[6]=0.3840;
//    xx[7]=0.6831;
//    xx[8]=0.0928;
//    xx[9]=0.0353;
//    xx[10]=0.6124;
//    xx[11]=0.6085;
//    xx[12]=0.0158;
//    xx[13]=0.0164;
//    xx[14]=0.1901;
//    xx[15]=0.5869;
//    tryFFT(xx,yy,16,16);

//    Complex xx[16],yy[16];int m=16;
//    xx[0].Update(0.5751,0);
//    xx[1].Update(0.4514,0);
//    xx[2].Update(0.0439,0);
//    xx[3].Update(0.0272,0);
//    xx[4].Update(0.3127,0);
//    xx[5].Update(0.0129,0);
//    xx[6].Update(0.3840,0);
//    xx[7].Update(0.6831,0);
//    xx[8].Update(0.0928,0);;
//    xx[9].Update(0.0353,0);
//    xx[10].Update(0.6124,0);
//    xx[11].Update(0.6085,0);
//    xx[12].Update(0.0158,0);
//    xx[13].Update(0.0164,0);
//    xx[14].Update(0.1901,0);
//    xx[15].Update(0.5869,0);
//    FFT(xx,yy,1024);

//    for(int i=0;i<16;i++)
//        qDebug()<<xx[i]<<"  "<<yy[i]<<"\n";

    //FFT(signal,result,SAMPLE);
    //FFT(DataArray,DataImage,SAMPLE,true);
    //CFFT(DataArray,DataArray,SIZE);
//    for(int i=0;i<SAMPLE;i++)
//    {
//        data.push_back(result[i].Abs());
//    }
//    DataVector.assign(data.begin(),data.end());
//}

//void MainWindow::Convolution(DrawType type, vector<double> RawData)
//{
//    int firLen = FirCoeff.size();
//    int sigLen = RawData.size();
//    double Result[firLen+sigLen-1];     // do convolution
//    for (int i = 0; i < firLen+sigLen-1; i++)
//    {
//        double min,max;

//        Result[i] = 0.0;
//        min=(i>=firLen-1) ? i-(firLen-1):0;
//        max=(i<sigLen-1) ? i:sigLen-1;

//        for(int j=min;j<=max;j++)
//        {
//            Result[i]+=FirCoeff[j] * RawData[i-j];
//        }
//    }     // set value to the output array

//    switch (type) {
//    case xAxisFilted:
//        for (int i = 0; i < sigLen; i++)
//            xVectorFilted.push_back(Result[i]);
//        break;
//    case yAxisFilted:
//        for (int i = 0; i < sigLen; i++)
//            yVectorFilted.push_back(Result[i]);
//        break;
//    case zAxisFilted:
//        for (int i = 0; i < sigLen; i++)
//            yVectorFilted.push_back(Result[i]);
//        break;
//    case oAxisFilted:
//        for (int i = 0; i < sigLen; i++)
//            FirResult.push_back(Result[i]);
//        break;
//    default:
//        break;
//    }
//}


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
