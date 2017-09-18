#include "FileManage.h"
#include <string>
#include <fstream>
#include "qcustomplot.h"
#include "ui_mainwindow.h"

FileManage::FileManage()
{
    QString fileFull;
    QFileInfo fileInfo;
    fileFull=QFileDialog::getOpenFileName();
    fileInfo=QFileInfo(fileFull);
    fileName=fileInfo.fileName().toStdString();
    fileSuffix=fileInfo.suffix().toStdString();
    filePath=fileInfo.absoluteFilePath().toStdString();
}

void FileManage::DrawRawData()
{
    if(coVector.size()!=0)
    {
        QCustomPlot *pRawDataPlot=new QCustomPlot();
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

int FileManage::Open()
{
    if(fileSuffix == "csv")
    {
        return ReadCSV();
    }
    else if(fileSuffix == "xlsx")
    {
        ReadExcel();
    }
    else if(fileSuffix == "txt")
    {
        ReadTxt();
    }
    else
    {

    }

    return 0;
}

int FileManage::ReadCSV()
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

void FileManage::ReadExcel()
{
    FILE *file;
    if(fopen_s(&file,filePath.c_str(),"r"))
    {
        while (true) {
            int reg = fscanf(file,"%lf,%lf,%lf\n", &coor.x,&coor.y,&coor.z);
            if(reg==3)
            {
                coVector.push_back(coor);
            }
            else
                break;
        }
        fclose(file);
    }
}

void FileManage::ReadTxt()
{
    ifstream iFile(filePath);
    if(iFile.is_open())
    {
        while(!iFile.eof())
        {
            iFile.getline(buffer,256);
            int reg=sscanf_s(buffer,"%lf,%lf,%lf",&coor.x,&coor.y,&coor.z);
            if(reg==3)
                coVector.push_back(coor);
            else
                continue;
        }
        iFile.close();
    }
    else
    {
         qDebug()<<"Cannot open the file!\n";
        return;
    }
}

void FileManage::FIRFilter()
{

}
