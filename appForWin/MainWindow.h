#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <FileManage.h>
#include "FileViewerDialog.h"

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
    Ui::MainWindow *ui;
    FileManage *fm;
    FileViewerDialog *fvd;

private slots:
    void fileOpen();

private:
    void DrawRawData();

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
};

#endif // MAINWINDOW_H
