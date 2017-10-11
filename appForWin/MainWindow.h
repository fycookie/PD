#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <string>
#include <QRubberBand>
#include "qcustomplot.h"
#include "editwindow.h"

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
    enum PlotType{
        AxisRawDataX,
        AxisRawDataY,
        AxisRawDataZ,
        AxisRawDataO,
        AxisFiltedX,
        AxisFiltedY,
        AxisFiltedZ,
        AxisFiltedO,
        AxisFFTedX,
        AxisFFTedY,
        AxisFFTedZ,
        AxisFFTedO,
        AxisTXT
    };

private:
    char buffer[256];
    int SAMPLE=256;
    int NumData=12000;

private:
    Ui::MainWindow *ui;
    QRubberBand *rubberBand;
    QPoint rubberOrigin;
    QButtonGroup *plotGroup;
    editwindow *edit;

private:
    vector<double> VectorT;
    vector<double> VectorX;
    vector<double> VectorY;
    vector<double> VectorZ;
    vector<double> VectorO;
    vector<double> VectorRawDataT;
    vector<double> VectorRawDataX;
    vector<double> VectorRawDataY;
    vector<double> VectorRawDataZ;
    vector<double> VectorRawDataO;
    vector<double> VectorFilterX;
    vector<double> VectorFilterY;
    vector<double> VectorFilterZ;
    vector<double> VectorFilterO;
    vector<double> VectorFFTX;
    vector<double> VectorFFTY;
    vector<double> VectorFFTZ;
    vector<double> VectorFFTO;
    vector<double> VectorFFTT;

    vector<double> VectorTxtX;
    vector<double> VectorTxtY;

private slots:
    void SlotMouseMove(QMouseEvent* mevent);
    void SlotMousePress(QMouseEvent* mevent);
    void SlotMouseRelease(QMouseEvent *mevent);
    void SlotResetBtn();
    void SlotFileOpen();
    void SlotPlotBtn();
    void SlotAxisX();
    void SlotAxisY();
    void SlotAxisZ();
    void SlotAxisO();
    void SlotFeatures();
    void SlotCutData();
    void SlotResetInput();

private:
    int ReadCSV(string filePath);
    int ReadTXT(string filePath);
    void PlotRawData();
    void PlotFiltData();
    void PlotFFTData();
    void DrawData(QCustomPlot *plot,
                  vector<double> xx,
                  vector<double> yy,
                  PlotType TYPE);
    void GetFFTData(vector<double> &DataVector,
                    PlotType TYPE);
    void ZoomDraw(vector<double> &xx,
                  vector<double> &yy,
                  PlotType TYPE);
    void GetFilterData(const vector<double> &signal,
              const vector<double> &filter,
              PlotType TYPE);
    void Convolution(const vector<double> &signal,
                     const vector<double> &filter,
                     PlotType TYPE);

    void DrawDataTXT();
};

#endif // MAINWINDOW_H
