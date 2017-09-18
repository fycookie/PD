#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include "qcustomplot.h"
#include <QFileInfo>
#include <QFileDialog>
#include <fstream>
//#include "FileManage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMaximumSize(600,400);
    this->setMinimumSize(400,300);
    ui->rawDataPlotBtn->setEnabled(false);
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(fileOpen()));
    connect(ui->rawDataPlotBtn,SIGNAL(clicked()),this,SLOT(DrawRawData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileOpen()
{
//    fvd = new FileViewerDialog();
//    fvd->show();
//    QString file="file://";
//    QDesktopServices::openUrl(QUrl(file,QUrl::TolerantMode));

//    QString file_full,file_name,file_path;
//    QFileInfo fi;
//    file_full=QFileDialog::getOpenFileName(this);
//    fi=QFileInfo(file_full);
//    file_name=fi.fileName();
//    file_path=fi.absoluteFilePath();

//    QFile file(file_path);
//    if(!file.open(QIODevice::ReadOnly))
//    {
//        qDebug()<<"Cannot open the file!";
//        return;
//    }

//    fm = new FileManage();
//    int reg=fm->Open();
//    if(reg>0)
//        ui->rawDataPlotBtn->setEnabled(true);

    QString fileFull;
    QFileInfo fileInfo;
    fileFull=QFileDialog::getOpenFileName();
    fileInfo=QFileInfo(fileFull);
    string fileName=fileInfo.fileName().toStdString();
    string fileSuffix=fileInfo.suffix().toStdString();
    string filePath=fileInfo.absoluteFilePath().toStdString();
    if(fileSuffix == "csv")
    {
        ReadCSV(filePath);
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
                coVector.push_back(coor);
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

void MainWindow::DrawRawData()
{
    if(coVector.size()!=0)
    {
        QCustomPlot *pRawDataPlot=new QCustomPlot(ui->graphicsView);
        pRawDataPlot->resize(200,300);
        QVector<double> t(1024),x(1024),y(1024),z(1024);
        int i=0;
        for(auto item:coVector)
        {
            t[i]=item.t;
            x[i]=item.x;
            y[i]=item.y;
            z[i]=item.z;
            i++;
            if(i>coVector.size())
                break;
        }

        pRawDataPlot->addGraph();
        pRawDataPlot->graph(0)->setPen(QPen(Qt::red));
        pRawDataPlot->graph(0)->setData(t,x);
        pRawDataPlot->graph(0)->setName("x axis");

        pRawDataPlot->addGraph();
        pRawDataPlot->graph(1)->setPen(QPen(Qt::blue));
        pRawDataPlot->graph(1)->setData(t,y);
        pRawDataPlot->graph(1)->setName("y axis");

        pRawDataPlot->addGraph();
        pRawDataPlot->graph(2)->setPen(QPen(Qt::yellow));
        pRawDataPlot->graph(2)->setData(t,z);
        pRawDataPlot->graph(2)->setName("z axis");

        pRawDataPlot->xAxis->setLabel("t/s");
        pRawDataPlot->yAxis->setLabel("a/mm");
        pRawDataPlot->setBackground(QColor(50,50,50));
    }
}


























