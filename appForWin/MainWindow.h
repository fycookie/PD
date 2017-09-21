#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <vector>
#include <string>
#include "firfilter.h"
#include <QRubberBand>
#include "qcustomplot.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    enum DrawType{xAxisRawData,
                  yAxisRawData,
                  zAxisRawData,
                  oAxisRawData,
                  xAxisFilted,
                  yAxisFilted,
                  zAxisFilted,
                  oAxisFilted,
                  xAxisFFT,
                  yAxisFFT,
                  zAxisFFT,
                  oAxisFFT};

    enum AxisType{
        xAxis,yAxis,zAxis,oAxis
    };

    enum FFTType{
        xFFT,yFFT,zFFT,oFFT
    };

private:
    struct Coordinate
    {
        double t=0.0;
        double x=0.0;
        double y=0.0;
        double z=0.0;
        operator=(Coordinate& other)
        {
            t=other.t;
            x=other.x;
            y=other.y;
            z=other.z;
        }
    };
    Coordinate coor;
    vector<Coordinate> coVector;

private:
    int ReadCSV(string filePath);
    //void ReadExcel(string filePath);
    //void ReadTxt(string filePath);

private:
    char buffer[256];
    string cache;
    string fileName;
    string filePath;
    string fileSuffix;
    QButtonGroup *plotGroup;

private:
    Ui::MainWindow *ui;
    vector<double> FirCoeff;
    vector<double> Signal;
    vector<double> FirResult;
    vector<double> tVectorRawData;
    vector<double> xVectorRawData;
    vector<double> yVectorRawData;
    vector<double> zVectorRawData;
    vector<double> xVectorFilted;
    vector<double> yVectorFilted;
    vector<double> zVectorFilted;
    vector<double> xVectorFFT;
    vector<double> yVectorFFT;
    vector<double> zVectorFFT;
    vector<double> oVectorFFT;
    vector<double> xxFFT;

    QRubberBand *rubberBand;
    QPoint rubberOrigin;

private:


private:
    void FIRCall();
    //void Convolution(DrawType type, vector<double> RawData);
    void Zoom(vector<double> xx,
              vector<double> yy);
    void DrawData(QCustomPlot *plot,
                     vector<double> xx,
                     vector<double> yy);

private slots:
    void mouseMove(QMouseEvent* mevent);
    void mousePress(QMouseEvent* mevent);
    void mouseRelease(QMouseEvent *mevent);
    void slotBtn();

    void fileOpen();
    void rdbtnSlot();
    //void axisSelect(AxisType type);
    void drawWithZoom(DrawType type);
    //void drawRawData();
    //void drawFiltedData();
    void axisX();
    void axisY();
    void axisZ();
    void axisO();

private:
    void drawRawData();
    void drawFiltedData();
    void Convolution();
    void FFTData(vector<double> &DataVector);
    void drawFFT();
    void DrawFFTAxis(QCustomPlot *plot,
                     vector<double> xx,
                     vector<double> yy);
    void MYFFT(vector<double> A, int N, bool ifft);
    int SAMPLE=256;
};

#endif // MAINWINDOW_H
