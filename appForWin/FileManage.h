#ifndef FILEMANAGE_H
#define FILEMANAGE_H

#include <QFile>
#include <vector>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QDebug>
#include "DataHandle.h"
#include "qcustomplot.h"

using namespace std;

class FileManage
{
public:
    FileManage();
    ~FileManage() {}

public:
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
    int ReadCSV();
    void ReadExcel();
    void ReadTxt();

public:
    void DrawRawData();

public:
    int Open();
    void FIRFilter();

private:
    DataHandle *dh;

private:
    char buffer[256];
    string cache;
    string fileName;
    string filePath;
    string fileSuffix;
};

#endif // FILEMANAGE_H
