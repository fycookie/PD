#include "MainWindow.h"
#include "qcustomplot.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <fstream>
#include "complex.h"
#include "FirCoeff.h"
#include "cfft.h"
#include <vector>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    connect(ui->actionOpen,SIGNAL(triggered()),
            this,SLOT(SlotFileOpen()));
    connect(ui->actionClose,SIGNAL(triggered()),
            this,SLOT(close()));

    rubberBand = new QRubberBand(QRubberBand::Rectangle,
                                 ui->widgetPlotZoom);
    connect(ui->widgetPlotZoom, SIGNAL(mousePress(QMouseEvent*)),
            this, SLOT(SlotMousePress(QMouseEvent*)));
    connect(ui->widgetPlotZoom, SIGNAL(mouseMove(QMouseEvent*)),
            this, SLOT(SlotMouseMove(QMouseEvent*)));
    connect(ui->widgetPlotZoom, SIGNAL(mouseRelease(QMouseEvent*)),
            this, SLOT(SlotMouseRelease(QMouseEvent*)));
    connect(ui->resetBtn, SIGNAL(clicked()),
            this, SLOT(SlotResetBtn()));

    connect(ui->rdbtnRawData,SIGNAL(clicked(bool)),
            this,SLOT(SlotPlotBtn()));
    connect(ui->rdbtnFiltData,SIGNAL(clicked(bool)),
            this,SLOT(SlotPlotBtn()));
    connect(ui->rdbtnFFT,SIGNAL(clicked(bool)),
            this,SLOT(SlotPlotBtn()));

    connect(ui->btnCutData,SIGNAL(clicked(bool)),
            this,SLOT(SlotCutData()));
    connect(ui->btnResetInput,SIGNAL(clicked(bool)),
            this,SLOT(SlotResetInput()));

    connect(ui->xAxisBtn,SIGNAL(clicked()),this,SLOT(SlotAxisX()));
    connect(ui->yAxisBtn,SIGNAL(clicked()),this,SLOT(SlotAxisY()));
    connect(ui->zAxisBtn,SIGNAL(clicked()),this,SLOT(SlotAxisZ()));
    connect(ui->oAxisBtn,SIGNAL(clicked()),this,SLOT(SlotAxisO()));

    connect(ui->actionFeatures,SIGNAL(triggered(bool)),
            this,SLOT(SlotFeatures()));

    this->setStyleSheet("border-image:url(./icon/mainwindow_map.jpg)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotCutData()
{
    if(ui->lineEditCutDataBeginWith->text().toDouble()>
       ui->lineEditCutDataEndWith->text().toDouble())
    {
        QMessageBox::information(NULL, "Warning",
                     "Begin number cannot be bigger than end number!",
                     QMessageBox::Yes);
        return;
    }

    VectorRawDataT.clear();
    VectorRawDataX.clear();
    VectorRawDataY.clear();
    VectorRawDataZ.clear();
    VectorRawDataO.clear();
    VectorFilterO.clear();
    VectorFilterX.clear();
    VectorFilterY.clear();
    VectorFilterZ.clear();
    VectorFFTO.clear();
    VectorFFTX.clear();
    VectorFFTY.clear();
    VectorFFTZ.clear();

    for(int i=0;i<VectorT.size();i++)
    {
        if(VectorT[i]<ui->lineEditCutDataBeginWith->text().toDouble())
            continue;
        else
        {
            if(VectorT[i]>ui->lineEditCutDataEndWith->text().toDouble())
                break;

            VectorRawDataT.push_back(VectorT[i]);
            VectorRawDataO.push_back(VectorO[i]);
            VectorRawDataX.push_back(VectorX[i]);
            VectorRawDataY.push_back(VectorY[i]);
            VectorRawDataZ.push_back(VectorZ[i]);
        }
    }
}

void MainWindow::SlotResetInput()
{
    VectorRawDataT.clear();
    VectorRawDataX.clear();
    VectorRawDataY.clear();
    VectorRawDataZ.clear();
    VectorRawDataO.clear();
    VectorFilterO.clear();
    VectorFilterX.clear();
    VectorFilterY.clear();
    VectorFilterZ.clear();
    VectorFFTO.clear();
    VectorFFTX.clear();
    VectorFFTY.clear();
    VectorFFTZ.clear();

    VectorRawDataT.assign(VectorT.begin(),VectorT.end());
    VectorRawDataX.assign(VectorX.begin(),VectorX.end());
    VectorRawDataY.assign(VectorY.begin(),VectorY.end());
    VectorRawDataZ.assign(VectorZ.begin(),VectorZ.end());
    VectorRawDataO.assign(VectorO.begin(),VectorO.end());
}

void MainWindow::SlotFeatures()
{
    vector<double> data;
    vector<double> freq;
    data.assign(VectorRawDataO.begin(),VectorRawDataO.end());
    freq.assign(VectorFFTO.begin(),VectorFFTO.end());
    edit = new editwindow(NULL,data,freq);
    edit->setWindowModality(Qt::ApplicationModal);
    edit->setAttribute(Qt::WA_ShowModal,false);
    connect(edit,SIGNAL(toMainWindow()), this, SLOT(showNormal()));
    //this->hide();
    edit->show();
    return;
}

void MainWindow::SlotFileOpen()
{
    QString fileFull;
    QFileInfo fileInfo;
    fileFull=QFileDialog::getOpenFileName();
    fileInfo=QFileInfo(fileFull);
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
    if(fileSuffix == "txt")
    {
        int reg = ReadTXT(filePath);
        if(reg >0)
        {
            ui->rdbtnRawData->setEnabled(true);
            ui->rdbtnFiltData->setEnabled(true);
            ui->rdbtnFFT->setEnabled(true);
        }
        DrawDataTXT();
    }
}

void MainWindow::DrawDataTXT()
{
    if(VectorTxtX.size()>0)
    {
        GetFFTData(VectorTxtX,AxisTXT);

        for(int i=0;i<SAMPLE;i++)
            VectorFFTT.push_back(100.0*i/SAMPLE);

        DrawData(ui->widgetplotX,VectorFFTT,VectorTxtY,AxisFFTedX);
    }
}

int MainWindow::ReadCSV(string filePath)
{
    ifstream iFile(filePath);
    if(iFile.is_open())
    {
        double t=0.0,x=0.0,y=0.0,z=0.0;
        while(!iFile.eof())
        {
            iFile.getline(buffer,256);
            int reg=sscanf_s(buffer,"%lf,%lf,%lf,%lf",&t,&x,&y,&z);
            if(reg==4)
            {
                VectorT.push_back(t);
                VectorX.push_back(x);
                VectorY.push_back(y);
                VectorZ.push_back(z);
                VectorO.push_back(sqrt(x*x+y*y+z*z));
                VectorRawDataT.push_back(t);
                VectorRawDataX.push_back(x);
                VectorRawDataY.push_back(y);
                VectorRawDataZ.push_back(z);
                VectorRawDataO.push_back(sqrt(x*x+y*y+z*z));
            }
            else
                continue;
        }
        iFile.close();
    }
    else
    {
        qDebug()<<"Cannot open the file!\n";
    }
    return VectorRawDataO.size();
}

int MainWindow::ReadTXT(string filePath)
{
    ifstream iFile(filePath);
    if(iFile.is_open())
    {
        double x=0.0;
        while(!iFile.eof())
        {
            iFile.getline(buffer,256);
            int reg=sscanf_s(buffer,"%lf",&x);
            if(reg==1)
            {
                VectorTxtX.push_back(x);
            }
            else
                continue;
        }
        iFile.close();
    }
    else
    {
        qDebug()<<"Cannot open the file!\n";
    }
    return VectorTxtX.size();
}

void MainWindow::SlotMouseMove(QMouseEvent *mevent)
{
    if(rubberBand->isVisible())
        rubberBand->setGeometry(QRect(rubberOrigin,mevent->pos()).normalized());
}

void MainWindow::SlotMousePress(QMouseEvent *mevent)
{
    if(mevent->button()==Qt::RightButton)
    {
        rubberOrigin=mevent->pos();
        rubberBand->setGeometry(QRect(rubberOrigin,QSize()));
        rubberBand->show();
    }
}

void MainWindow::SlotMouseRelease(QMouseEvent *mevent)
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

void MainWindow::SlotAxisX()
{
    if(plotGroup->checkedId()==0)
        ZoomDraw(VectorRawDataT,VectorRawDataX,AxisRawDataX);
    else if(plotGroup->checkedId()==1)
        ZoomDraw(VectorRawDataT,VectorFilterX,AxisFiltedX);
    else if(plotGroup->checkedId()==2)
        ZoomDraw(VectorFFTT,VectorFFTX,AxisFFTedX);
}

void MainWindow::SlotAxisY()
{
    if(plotGroup->checkedId()==0)
        ZoomDraw(VectorRawDataT,VectorRawDataY,AxisRawDataY);
    else if(plotGroup->checkedId()==1)
        ZoomDraw(VectorRawDataT,VectorFilterY,AxisFiltedY);
    else if(plotGroup->checkedId()==2)
        ZoomDraw(VectorFFTT,VectorFFTY,AxisFFTedY);
}

void MainWindow::SlotAxisZ()
{
    if(plotGroup->checkedId()==0)
        ZoomDraw(VectorRawDataT,VectorRawDataZ,AxisRawDataZ);
    else if(plotGroup->checkedId()==1)
        ZoomDraw(VectorRawDataT,VectorFilterZ,AxisFiltedZ);
    else if(plotGroup->checkedId()==2)
        ZoomDraw(VectorFFTT,VectorFFTZ,AxisFFTedZ);
}

void MainWindow::SlotAxisO()
{
    if(plotGroup->checkedId()==0)
        ZoomDraw(VectorRawDataT,VectorRawDataO,AxisRawDataO);
    else if(plotGroup->checkedId()==1)
        ZoomDraw(VectorRawDataT,VectorFilterO,AxisFiltedO);
    else if(plotGroup->checkedId()==2)
        ZoomDraw(VectorFFTT,VectorFFTO,AxisFFTedO);
}

void MainWindow::SlotResetBtn()
{
    ui->widgetPlotZoom->rescaleAxes();
    ui->widgetPlotZoom->replot();
}

void MainWindow::SlotPlotBtn()
{
    if(plotGroup->checkedId()==0)
        PlotRawData();
    else if(plotGroup->checkedId()==1)
        PlotFiltData();
    else if(plotGroup->checkedId()==2)
        PlotFFTData();
}

void MainWindow::PlotRawData()
{
    ui->widgetplotX->setVisible(false);
    ui->widgetplotY->setVisible(false);
    ui->widgetplotZ->setVisible(false);
    ui->widgetplotO->setVisible(false);
    ui->widgetPlotZoom->setVisible(false);

    if(VectorRawDataT.size()>0 && VectorRawDataX.size()>0)
        DrawData(ui->widgetplotX, VectorRawDataT,
                 VectorRawDataX,AxisRawDataX);

    if(VectorRawDataT.size()>0 && VectorRawDataY.size()>0)
        DrawData(ui->widgetplotY, VectorRawDataT,
                 VectorRawDataY,AxisRawDataY);

    if(VectorRawDataT.size()>0 && VectorRawDataZ.size()>0)
        DrawData(ui->widgetplotZ, VectorRawDataT,
                 VectorRawDataZ,AxisRawDataZ);

    if(VectorRawDataT.size()>0 && VectorRawDataO.size()>0)
        DrawData(ui->widgetplotO, VectorRawDataT,
                 VectorRawDataO,AxisRawDataO);
}

void MainWindow::PlotFiltData()
{
    ui->widgetplotX->setVisible(false);
    ui->widgetplotY->setVisible(false);
    ui->widgetplotZ->setVisible(false);
    ui->widgetplotO->setVisible(false);
    ui->widgetPlotZoom->setVisible(false);

    if(VectorRawDataO.size()>0 )
    {
        if(VectorFilterO.size()==0)
        {
            vector<double> filter;
            for(int i=0;i<NL;i++)
                filter.push_back(NUM[i]);

            GetFilterData(VectorRawDataX, filter,AxisFiltedX);
            GetFilterData(VectorRawDataY, filter,AxisFiltedY);
            GetFilterData(VectorRawDataZ, filter,AxisFiltedZ);
            GetFilterData(VectorRawDataO, filter,AxisFiltedO);
        }

        if(VectorRawDataX.size()>0 && VectorRawDataT.size()>0)
            DrawData(ui->widgetplotX, VectorRawDataT,
                     VectorFilterX, AxisFiltedX);

        if(VectorRawDataY.size()>0 && VectorRawDataT.size()>0)
            DrawData(ui->widgetplotY, VectorRawDataT,
                     VectorFilterY, AxisFiltedY);

        if(VectorRawDataZ.size()>0 && VectorRawDataT.size()>0)
            DrawData(ui->widgetplotZ, VectorRawDataT,
                     VectorFilterZ, AxisFiltedZ);

        if(VectorRawDataO.size()>0 && VectorRawDataT.size()>0)
            DrawData(ui->widgetplotO, VectorRawDataT,
                     VectorFilterO, AxisFiltedO);
    }
}

void MainWindow::PlotFFTData()
{
    if(VectorFFTO.size()<1)
    {
        GetFFTData(VectorRawDataX,AxisFFTedX);
        GetFFTData(VectorRawDataY,AxisFFTedY);
        GetFFTData(VectorRawDataZ,AxisFFTedZ);
        GetFFTData(VectorRawDataO,AxisFFTedO);

        for(int i=0;i<SAMPLE;i++)
            VectorFFTT.push_back(100.0*i/SAMPLE);
    }
    DrawData(ui->widgetplotX,VectorFFTT,VectorFFTX,AxisFFTedX);
    DrawData(ui->widgetplotY,VectorFFTT,VectorFFTY,AxisFFTedY);
    DrawData(ui->widgetplotZ,VectorFFTT,VectorFFTZ,AxisFFTedZ);
    DrawData(ui->widgetplotO,VectorFFTT,VectorFFTO,AxisFFTedO);
}

void MainWindow::DrawData(QCustomPlot *plot,
                          vector<double> xx,
                          vector<double> yy,
                          PlotType TYPE)
{
    ui->widgetplotX->setVisible(true);
    ui->widgetplotY->setVisible(true);
    ui->widgetplotZ->setVisible(true);
    ui->widgetplotO->setVisible(true);
    ui->widgetPlotZoom->setVisible(false);

    int SIZEX = xx.size();
    int SIZEY = yy.size();
    QVector<double> x(SIZEX),y(SIZEY);
    int i=0;
    for(auto item:xx)
    {
        x[i]=item;
        i++;
    }
    int j=0;
    for(auto item:yy)
    {
        y[j]=item;
        j++;
    }
    plot->addGraph();
    plot->replot();
    plot->graph(0)->setPen(QPen(Qt::blue));
    plot->graph(0)->setData(x,y);
    plot->setBackground(QColor(100,150,50));

    switch (TYPE) {
    case AxisRawDataX:
    case AxisRawDataY:
    case AxisRawDataZ:
    case AxisRawDataO:
    case AxisFiltedX:
    case AxisFiltedY:
    case AxisFiltedZ:
    case AxisFiltedO:
    {
        plot->xAxis->setLabel("t/s");
        plot->yAxis->setLabel("a/mm^2");
        break;
    }
    case AxisFFTedX:
    case AxisFFTedY:
    case AxisFFTedZ:
    case AxisFFTedO:
    {
        plot->xAxis->setLabel("fs/Hz");
        plot->yAxis->setLabel("a/mm^2");
        break;
    }
    default:
        break;
    }

    plot->rescaleAxes();
    plot->replot();
}

void MainWindow::GetFilterData(const vector<double> &signal,
                      const vector<double> &filter,
                      PlotType TYPE)
{
    if( signal.size() < filter.size() )
        Convolution( filter,signal,TYPE);
    else
        Convolution( signal,filter,TYPE);
}

void MainWindow::GetFFTData(vector<double> &DataVector,PlotType TYPE)
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

    switch (TYPE) {
    case AxisFFTedX:
        for(int i=0;i<SAMPLE;i++)
            VectorFFTX.push_back(yy[i].Abs());
        break;
    case AxisFFTedY:
        for(int i=0;i<SAMPLE;i++)
            VectorFFTY.push_back(yy[i].Abs());
        break;
    case AxisFFTedZ:
        for(int i=0;i<SAMPLE;i++)
            VectorFFTZ.push_back(yy[i].Abs());
        break;
    case AxisFFTedO:
        for(int i=0;i<SAMPLE;i++)
            VectorFFTO.push_back(yy[i].Abs());
        break;
    case AxisTXT:
        for(int i=0;i<SAMPLE;i++)
            VectorTxtY.push_back(yy[i].Abs());
        break;
    default:
        break;
    }
}

void MainWindow::Convolution( const vector<double> &signal,
                              const vector<double> &filter,
                              PlotType TYPE)
{
    int sigLength = signal.size();
    int filLength = filter.size();
    //assert( sigLength >= filLength );

    int length = sigLength + filLength - 1;
    vector<double> x;
    for(int i=0;i<length;i++)
        x.push_back(0.0);

    for( int i=1; i<=length; ++i )
    {
        x[i] = 0;
        if( i < filLength )
            for( int j=1; j<=i; ++j )
                x[i] += filter[j] * signal[i-j+1];
        else if( i <= sigLength )
            for( int j=1; j<=filLength; ++j )
                x[i] += filter[j] * signal[i-j+1];
        else
            for( int j=i-sigLength+1; j<=filLength; ++j )
                x[i] += filter[j] * signal[i-j+1];
    }

    switch (TYPE) {
    case AxisFiltedX:
        for(int i=0;i<x.size();i++)
            VectorFilterX.push_back(x[i]);
        break;
    case AxisFiltedY:
        for(int i=0;i<x.size();i++)
            VectorFilterY.push_back(x[i]);
        break;
    case AxisFiltedZ:
        for(int i=0;i<x.size();i++)
            VectorFilterZ.push_back(x[i]);
        break;
    case AxisFiltedO:
        for(int i=0;i<x.size();i++)
            VectorFilterO.push_back(x[i]);
        break;
    default:
        break;
    }
}

void MainWindow::ZoomDraw(vector<double> &xx,
                          vector<double> &yy,
                          PlotType TYPE)
{
    ui->widgetplotX->setVisible(false);
    ui->widgetplotY->setVisible(false);
    ui->widgetplotZ->setVisible(false);
    ui->widgetplotO->setVisible(false);
    ui->widgetPlotZoom->setVisible(true);

    int SIZEX=xx.size();
    int SIZEY=yy.size();
    QVector<double> x(SIZEX),y(SIZEY);
    int i=0;
    for(auto item:xx)
    {
        x[i]=item;
        i++;
    }
    int j=0;
    for(auto item:yy)
    {
        y[j]=item;
        j++;
    }

    QCustomPlot *pZoom=ui->widgetPlotZoom;
    pZoom->addGraph();
    pZoom->replot();
    pZoom->graph(0)->setPen(QPen(Qt::blue));
    pZoom->setBackground(QColor(100,150,50));

    switch (TYPE) {
    case AxisRawDataX:
    case AxisRawDataY:
    case AxisRawDataZ:
    case AxisRawDataO:
    case AxisFiltedX:
    case AxisFiltedY:
    case AxisFiltedZ:
    case AxisFiltedO:
    {
        pZoom->xAxis->setLabel("t/s");
        pZoom->yAxis->setLabel("a/mm^2");
        break;
    }
    case AxisFFTedX:
    case AxisFFTedY:
    case AxisFFTedZ:
    case AxisFFTedO:
    {
        pZoom->xAxis->setLabel("fs/Hz");
        pZoom->yAxis->setLabel("a/mm^2");
        break;
    }
    default:
        break;
    }
    pZoom->graph(0)->setData(x,y);
    pZoom->rescaleAxes();
    pZoom->replot();
}
























//#include "MainWindow.h"
//#include "ui_mainwindow.h"
//#include <QDesktopServices>
//#include <QUrl>
//#include <QDebug>
//#include "qcustomplot.h"
//#include <QFileInfo>
//#include <QFileDialog>
//#include <fstream>
//#include "constants.h"
//#include <fstream>
//#include "FFTCode.h"
//#include "FIRFilterCode.h"
//#include "math.h"
//#include <vector>
//#include <QButtonGroup>
//#include "cfft.h"
//#include "complex.h"
//#include "FirCoeff.h"

//using namespace std;

//MainWindow::MainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//    this->setMaximumSize(750,500);
//    this->setMinimumSize(600,450);
//    ui->widgetplotX->setVisible(false);
//    ui->widgetplotY->setVisible(false);
//    ui->widgetplotZ->setVisible(false);
//    ui->widgetplotO->setVisible(false);
//    ui->widgetPlotZoom->setVisible(false);

//    plotGroup=new QButtonGroup(this);
//    plotGroup->addButton(ui->rdbtnRawData,0);
//    plotGroup->addButton(ui->rdbtnFiltData,1);
//    plotGroup->addButton(ui->rdbtnFFT,2);
//    ui->rdbtnRawData->setEnabled(false);
//    ui->rdbtnFiltData->setEnabled(false);
//    ui->rdbtnFFT->setEnabled(false);

//    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(fileOpen()));
//    connect(ui->actionClose,SIGNAL(triggered()),this,SLOT(close()));
//    connect(ui->rdbtnRawData,SIGNAL(clicked()),this,SLOT(rdbtnSlot()));
//    connect(ui->rdbtnFiltData,SIGNAL(clicked()),this,SLOT(rdbtnSlot()));
//    connect(ui->rdbtnFFT,SIGNAL(clicked(bool)),this,SLOT(rdbtnSlot()));

//    connect(ui->xAxisBtn,SIGNAL(clicked()),this,SLOT(axisX()));
//    connect(ui->yAxisBtn,SIGNAL(clicked()),this,SLOT(axisY()));
//    connect(ui->zAxisBtn,SIGNAL(clicked()),this,SLOT(axisZ()));
//    connect(ui->oAxisBtn,SIGNAL(clicked()),this,SLOT(axisO()));

//    rubberBand = new QRubberBand(QRubberBand::Rectangle, ui->widgetPlotZoom);
//    connect(ui->widgetPlotZoom, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
//    connect(ui->widgetPlotZoom, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseMove(QMouseEvent*)));
//    connect(ui->widgetPlotZoom, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(mouseRelease(QMouseEvent*)));
//    connect(ui->resetBtn, SIGNAL(clicked()), this, SLOT(slotBtn()));
//}

//void MainWindow::rdbtnSlot()
//{
//    if(plotGroup->checkedId()==0)
//        drawRawData();
//    else if(plotGroup->checkedId()==1)
//        drawFiltedData();
//    else if(plotGroup->checkedId()==2)
//        drawFFT();
//}

//void MainWindow::axisX()
//{
//    if(plotGroup->checkedId()==0)
//        drawWithZoom(AxisRawDatax);
//    else if(plotGroup->checkedId()==1)
//        drawWithZoom(AxisFiltedx);
//    else if(plotGroup->checkedId()==2)
//        drawWithZoom(AxisFFTedx);
//}
//void MainWindow::axisY()
//{
//    if(plotGroup->checkedId()==0)
//        drawWithZoom(AxisRawDatay);
//    else if(plotGroup->checkedId()==1)
//        drawWithZoom(AxisFiltedy);
//    else if(plotGroup->checkedId()==2)
//        drawWithZoom(AxisFFTedy);
//}
//void MainWindow::axisZ()
//{
//    if(plotGroup->checkedId()==0)
//        drawWithZoom(AxisRawDataz);
//    else if(plotGroup->checkedId()==1)
//        drawWithZoom(AxisFiltedz);
//    else if(plotGroup->checkedId()==1)
//        drawWithZoom(AxisFFTedz);
//}
//void MainWindow::axisO()
//{
//    if(plotGroup->checkedId()==0)
//        drawWithZoom(AxisRawDatao);
//    else if(plotGroup->checkedId()==1)
//        drawWithZoom(AxisFiltedo);
//    else if(plotGroup->checkedId()==1)
//        drawWithZoom(AxisFFTedo);
//}

//void MainWindow::mouseMove(QMouseEvent *mevent)
//{
//    if(rubberBand->isVisible())
//        rubberBand->setGeometry(QRect(rubberOrigin,mevent->pos()).normalized());
//}

//void MainWindow::slotBtn()
//{
//    ui->widgetPlotZoom->rescaleAxes();
//    ui->widgetPlotZoom->replot();
//}

//void MainWindow::mousePress(QMouseEvent *mevent)
//{
//    if(mevent->button()==Qt::RightButton)
//    {
//        rubberOrigin=mevent->pos();
//        rubberBand->setGeometry(QRect(rubberOrigin,QSize()));
//        rubberBand->show();
//    }
//}

//void MainWindow::mouseRelease(QMouseEvent *mevent)
//{
//    Q_UNUSED(mevent);
//    if(rubberBand->isVisible())
//    {
//        const QRect zoomRect=rubberBand->geometry();
//        int xpOne,xpTwo,ypOne,ypTwo;
//        zoomRect.getCoords(&xpOne,&ypOne,&xpTwo,&ypTwo);

//        double xOne=ui->widgetPlotZoom->xAxis->pixelToCoord(xpOne);
//        double xTwo=ui->widgetPlotZoom->xAxis->pixelToCoord(xpTwo);
//        double yOne=ui->widgetPlotZoom->yAxis->pixelToCoord(ypTwo);
//        double yTwo=ui->widgetPlotZoom->yAxis->pixelToCoord(ypTwo);

//        ui->widgetPlotZoom->xAxis->setRange(xOne,xTwo);
//        ui->widgetPlotZoom->yAxis->setRange(yOne,yTwo);

//        rubberBand->hide();
//        ui->widgetPlotZoom->replot();
//    }
//}

//MainWindow::~MainWindow()
//{
//    delete ui;
//}

//void MainWindow::fileOpen()
//{
//    QString fileFull;
//    QFileInfo fileInfo;
//    fileFull=QFileDialog::getOpenFileName();
//    fileInfo=QFileInfo(fileFull);
//    string fileName=fileInfo.fileName().toStdString();
//    string fileSuffix=fileInfo.suffix().toStdString();
//    string filePath=fileInfo.absoluteFilePath().toStdString();
//    if(fileSuffix == "csv")
//    {
//        int reg = ReadCSV(filePath);
//        if(reg >0)
//        {
//            ui->rdbtnRawData->setEnabled(true);
//            ui->rdbtnFiltData->setEnabled(true);
//            ui->rdbtnFFT->setEnabled(true);
//        }
//    }
////    else if(fileSuffix == "xlsx")
////    {
////        ReadExcel(filePath);
////    }
////    else if(fileSuffix == "txt")
////    {
////        ReadTxt(filePath);
////    }
//    else
//    {

//    }
//}

//int MainWindow::ReadCSV(string filePath)
//{
//    ifstream iFile(filePath);
//    if(iFile.is_open())
//    {
//        while(!iFile.eof())
//        {
//            iFile.getline(buffer,256);
//            int reg=sscanf_s(buffer,"%lf,%lf,%lf,%lf",&coor.t,&coor.x,&coor.y,&coor.z);
//            if(reg==4)
//            {
//                coVector.push_back(coor);
//                tVectorRawData.push_back(coor.t);
//                xVectorRawData.push_back(coor.x);
//                yVectorRawData.push_back(coor.y);
//                zVectorRawData.push_back(coor.z);
//                Signal.push_back(sqrt(coor.x*coor.x+coor.y*coor.y+coor.z*coor.z));
//            }
//            else
//                continue;
//        }
//        iFile.close();
//    }
//    else
//    {
//        qDebug()<<"Cannot open the file!\n";
//    }
//    return coVector.size();
//}

////void MainWindow::mouseMove(QMouseEvent* event)
////{
////    int x_pos=event->pos().x();
////    int y_pos=event->pos().y();

////    // 把鼠标坐标点 转换为 QCustomPlot 内部坐标值 （pixelToCoord 函数）
////    // coordToPixel 函数与之相反 是把内部坐标值 转换为外部坐标点
////    double x_val = ui->widgetplotY->xAxis->pixelToCoord(x_pos);
////    double y_val = ui->widgetplotY->yAxis->pixelToCoord(y_pos);

////    // 然后打印在界面上
////    ui->textEdit->setText(tr("(%1\n  %2\n  ||\n  %3\n  %4)")
////                       .arg(x_pos).arg(y_pos).arg(x_val).arg(y_val));
////}

//void MainWindow::drawRawData()
//{
//    ui->widgetplotX->setVisible(false);
//    ui->widgetplotY->setVisible(false);
//    ui->widgetplotZ->setVisible(false);
//    ui->widgetplotO->setVisible(false);
//    ui->widgetPlotZoom->setVisible(false);

//    if(tVectorRawData.size()>0 && xVectorRawData.size()>0)
//        DrawData(ui->widgetplotX, tVectorRawData, xVectorRawData);
//    if(tVectorRawData.size()>0 && yVectorRawData.size()>0)
//        DrawData(ui->widgetplotY, tVectorRawData, yVectorRawData);
//    if(tVectorRawData.size()>0 && zVectorRawData.size()>0)
//        DrawData(ui->widgetplotZ, tVectorRawData, zVectorRawData);
//    if(tVectorRawData.size()>0 && Signal.size()>0)
//        DrawData(ui->widgetplotO, tVectorRawData, Signal);
//}

//void MainWindow::DrawFFTAxis(QCustomPlot *plot, vector<double> xx, vector<double> yy)
//{
//    ui->widgetplotX->setVisible(true);
//    ui->widgetplotY->setVisible(true);
//    ui->widgetplotZ->setVisible(true);
//    ui->widgetplotO->setVisible(true);
//    ui->widgetPlotZoom->setVisible(false);
//    plot->setVisible(false);
//    QVector<double> x(SAMPLE),y(SAMPLE);
//    for(int i=0;i<SAMPLE;i++)
//    {
//        x[i]=xx[i];
//        y[i]=yy[i];
//    }
//    QMargins margins(10,5,5,5);
//    plot->addGraph();
//    plot->xAxis->setRange(0,SAMPLE);
//    plot->graph(0)->setPen(QPen(Qt::yellow));
//    plot->xAxis->setLabel("fs/Hz");
//    plot->yAxis->setLabel("a/mm^2");
//    plot->axisRect()->setMargins(margins);
//    plot->setBackground(QColor(100,150,50));
//    plot->graph(0)->setData(x,y);
//    plot->yAxis->rescale();
//    plot->replot();
//}

//void MainWindow::DrawData(QCustomPlot *plot, vector<double> xx, vector<double> yy)
//{
//    ui->widgetplotX->setVisible(true);
//    ui->widgetplotY->setVisible(true);
//    ui->widgetplotZ->setVisible(true);
//    ui->widgetplotO->setVisible(true);
//    ui->widgetPlotZoom->setVisible(false);

//    plot->setVisible(false);
//    QVector<double> x(15000),y(15000);
//    int i=0;
//    for(auto item:xx)
//    {
//        x[i]=item;
//        i++;
//        if(i>10000)
//            break;
//    }
//    int j=0;
//    for(auto item:yy)
//    {
//        y[j]=item;
//        j++;
//        if(j>10000)
//            break;
//    }
//    plot->addGraph();
//    plot->xAxis->setRange(0,i);
//    plot->graph(0)->setPen(QPen(Qt::blue));
//    plot->graph(0)->setData(x,y);
//    plot->xAxis->setLabel("t/s");
//    plot->yAxis->setLabel("a/mm");
//    plot->setBackground(QColor(100,150,50));
//    plot->replot();
//}

//void MainWindow::drawWithZoom(PlotType PlotType)
//{
//    ui->widgetplotX->setVisible(false);
//    ui->widgetplotY->setVisible(false);
//    ui->widgetplotZ->setVisible(false);
//    ui->widgetplotO->setVisible(false);
//    ui->widgetPlotZoom->setVisible(true);
//    switch(PlotType)
//    {
//        case AxisRawDatax:
//            Zoom(tVectorRawData,xVectorRawData);
//            break;
//        case AxisRawDatay:
//            Zoom(tVectorRawData,yVectorRawData);
//            break;
//        case AxisRawDataz:
//            Zoom(tVectorRawData,zVectorRawData);
//            break;
//        case AxisRawDatao:
//            Zoom(tVectorRawData,Signal);
//            break;
//        case AxisFiltedx:
//            Zoom(tVectorRawData,xVectorFilted);
//            break;
//        case AxisFiltedy:
//            Zoom(tVectorRawData,yVectorFilted);
//            break;
//        case AxisFiltedz:
//            Zoom(tVectorRawData,zVectorFilted);
//            break;
//        case AxisFiltedo:
//            Zoom(tVectorRawData,FirResult);
//            break;
//        case AxisFFTedx:
//            Zoom(xFFTx,xVectorFFT);
//            break;
//        case AxisFFTedy:
//            Zoom(xFFTx,yVectorFFT);
//            break;
//        case AxisFFTedz:
//            Zoom(xFFTx,zVectorFFT);
//            break;
//        case AxisFFTedo:
//            Zoom(xFFTx,oVectorFFT);
//            break;
//    }
//}

//void MainWindow::Zoom(vector<double> xx, vector<double> yy)
//{
//    QVector<double> x(10000),y(10000);
//    int i=0;
//    for(auto item:xx)
//    {
//        x[i]=item;
//        i++;
//        if(i>10000)
//            break;
//    }
//    int j=0;
//    for(auto item:yy)
//    {
//        y[j]=item;
//        j++;
//        if(j>10000)
//            break;
//    }

//    QCustomPlot *pZoom=ui->widgetPlotZoom;
//    pZoom->addGraph();
//    pZoom->xAxis->setRange(0,i);
//    pZoom->graph(0)->setPen(QPen(Qt::blue));
//    pZoom->graph(0)->setData(x,y);
//    pZoom->xAxis->setLabel("t/s");
//    pZoom->yAxis->setLabel("a/mm");
//    pZoom->setBackground(QColor(100,150,50));
//    pZoom->yAxis->rescale();
//    pZoom->replot();
//    pZoom->show();
//}

//void MainWindow::drawFiltedData()
//{
//    ui->widgetplotX->setVisible(false);
//    ui->widgetplotY->setVisible(false);
//    ui->widgetplotZ->setVisible(false);
//    ui->widgetplotO->setVisible(false);
//    ui->widgetPlotZoom->setVisible(false);

//    if(Signal.size()>0)
//    {
//        if(FirResult.size()==0)
//        {
//            vector<double> filter;
//            for(int i=0;i<NL;i++)
//                filter.push_back(NUM[i]);

//            conv(zVectorRawData, filter,AxisFiltedx);
//            conv(xVectorRawData, filter,AxisFiltedy);
//            conv(yVectorRawData, filter,AxisFiltedz);
//            conv(Signal, filter,AxisFiltedo);
//        }

//        if(xVectorFilted.size()>0)
//        {
//            DrawData(ui->widgetplotX, tVectorRawData, xVectorFilted);
//        }
//        if(yVectorFilted.size()>0)
//        {
//            DrawData(ui->widgetplotY, tVectorRawData, yVectorFilted);
//        }
//        if(zVectorFilted.size()>0)
//        {
//            DrawData(ui->widgetplotZ, tVectorRawData, zVectorFilted);
//        }
//        if(FirResult.size()>0)
//        {
//            DrawData(ui->widgetplotO, tVectorRawData, FirResult);
//        }
//    }
//}

//void MainWindow::conv( const vector<double> &signal, const vector<double> &filter,PlotType PlotType)
//{
//    if( signal.size() < filter.size() )
//        convolution( filter, signal,PlotType);
//    else
//        convolution( signal, filter,PlotType);
//}

//void MainWindow::convolution( const vector<double> &signal,
//                            const vector<double> &filter,PlotType PlotType)
//{
//    int sigLength = signal.size();
//    int filLength = filter.size();

//    //assert( sigLength >= filLength );

//    int length = sigLength + filLength - 1;
//    vector<double> x;
//    for(int i=0;i<length;i++)
//        x.push_back(0.0);

//    for( int i=1; i<=length; ++i )
//    {
//        x[i] = 0;
//        if( i < filLength )
//            for( int j=1; j<=i; ++j )
//                x[i] += filter[j] * signal[i-j+1];
//        else if( i <= sigLength )
//            for( int j=1; j<=filLength; ++j )
//                x[i] += filter[j] * signal[i-j+1];
//        else
//            for( int j=i-sigLength+1; j<=filLength; ++j )
//                x[i] += filter[j] * signal[i-j+1];
//    }

//    switch (PlotType) {
//    case AxisFFTedo:
//        for(int i=0;i<SAMPLE;i++)
//            FirResult.push_back(x[i]);
//        break;
//    case AxisFFTedx:
//        for(int i=0;i<SAMPLE;i++)
//            xVectorFilted.push_back(x[i]);
//        break;
//    case AxisFFTedy:
//        for(int i=0;i<SAMPLE;i++)
//            yVectorFilted.push_back(x[i]);
//        break;
//    case AxisFFTedz:
//        for(int i=0;i<SAMPLE;i++)
//            zVectorFilted.push_back(x[i]);
//        break;
//    default:
//        break;
//    }
//}

//void MainWindow::drawFFT()
//{
//    if(oVectorFFT.size()<1)
//    {
//        FFTData(xVectorRawData,AxisFFTedx);
//        FFTData(yVectorRawData,AxisFFTedy);
//        FFTData(zVectorRawData,AxisFFTedz);
//        FFTData(Signal,AxisFFTedo);

//        for(int i=0;i<SAMPLE;i++)
//            xFFTx.push_back(100*i/SAMPLE);
//    }
//    DrawFFTAxis(ui->widgetplotX,xFFTx,xVectorFFT);
//    DrawFFTAxis(ui->widgetplotY,xFFTx,yVectorFFT);
//    DrawFFTAxis(ui->widgetplotZ,xFFTx,zVectorFFT);
//    DrawFFTAxis(ui->widgetplotO,xFFTx,oVectorFFT);
//}

//void MainWindow::FFTData(vector<double> &DataVector,PlotType PlotType)
//{
//    int SIZE=DataVector.size();
//    Complex xx[SIZE];
//    Complex yy[SAMPLE];
//    for(int i=0;i<SIZE;i++)
//    {
//        xx[i].Update(DataVector[i],0);
//    }
//    for(int i=0;i<SAMPLE;i++)
//    {
//        yy[i].Update(0,0);
//    }
//    FFT(xx,yy,SAMPLE);

//    switch (PlotType) {
//    case AxisFFTedo:
//        for(int i=0;i<SAMPLE;i++)
//            oVectorFFT.push_back(yy[i].Abs());
//        break;
//    case AxisFFTedx:
//        for(int i=0;i<SAMPLE;i++)
//            xVectorFFT.push_back(yy[i].Abs());
//        break;
//    case AxisFFTedy:
//        for(int i=0;i<SAMPLE;i++)
//            yVectorFFT.push_back(yy[i].Abs());
//        break;
//    case AxisFFTedz:
//        for(int i=0;i<SAMPLE;i++)
//            zVectorFFT.push_back(yy[i].Abs());
//        break;
//    default:
//        break;
//    }
//}
