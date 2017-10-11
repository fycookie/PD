/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionClose;
    QAction *actionFeatures;
    QAction *actionReport;
    QWidget *centralwidget;
    QCustomPlot *widgetplotX;
    QPushButton *xAxisBtn;
    QCustomPlot *widgetplotY;
    QPushButton *yAxisBtn;
    QCustomPlot *widgetplotZ;
    QPushButton *zAxisBtn;
    QPushButton *resetBtn;
    QCustomPlot *widgetplotO;
    QPushButton *oAxisBtn;
    QRadioButton *rdbtnRawData;
    QRadioButton *rdbtnFiltData;
    QRadioButton *rdbtnFFT;
    QCustomPlot *widgetPlotZoom;
    QLineEdit *lineEditCutDataBeginWith;
    QLabel *labelCutDataBeginWith;
    QLineEdit *lineEditCutDataEndWith;
    QLabel *labelCutDataEndWith;
    QPushButton *btnCutData;
    QPushButton *btnResetInput;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(927, 600);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionFeatures = new QAction(MainWindow);
        actionFeatures->setObjectName(QStringLiteral("actionFeatures"));
        actionReport = new QAction(MainWindow);
        actionReport->setObjectName(QStringLiteral("actionReport"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        widgetplotX = new QCustomPlot(centralwidget);
        widgetplotX->setObjectName(QStringLiteral("widgetplotX"));
        widgetplotX->setGeometry(QRect(130, 20, 761, 111));
        xAxisBtn = new QPushButton(widgetplotX);
        xAxisBtn->setObjectName(QStringLiteral("xAxisBtn"));
        xAxisBtn->setGeometry(QRect(690, 90, 75, 23));
        widgetplotY = new QCustomPlot(centralwidget);
        widgetplotY->setObjectName(QStringLiteral("widgetplotY"));
        widgetplotY->setGeometry(QRect(130, 160, 761, 111));
        yAxisBtn = new QPushButton(widgetplotY);
        yAxisBtn->setObjectName(QStringLiteral("yAxisBtn"));
        yAxisBtn->setGeometry(QRect(690, 90, 75, 23));
        widgetplotZ = new QCustomPlot(centralwidget);
        widgetplotZ->setObjectName(QStringLiteral("widgetplotZ"));
        widgetplotZ->setGeometry(QRect(130, 300, 761, 111));
        zAxisBtn = new QPushButton(widgetplotZ);
        zAxisBtn->setObjectName(QStringLiteral("zAxisBtn"));
        zAxisBtn->setGeometry(QRect(690, 90, 75, 23));
        resetBtn = new QPushButton(centralwidget);
        resetBtn->setObjectName(QStringLiteral("resetBtn"));
        resetBtn->setGeometry(QRect(20, 150, 75, 23));
        widgetplotO = new QCustomPlot(centralwidget);
        widgetplotO->setObjectName(QStringLiteral("widgetplotO"));
        widgetplotO->setGeometry(QRect(130, 440, 761, 111));
        oAxisBtn = new QPushButton(widgetplotO);
        oAxisBtn->setObjectName(QStringLiteral("oAxisBtn"));
        oAxisBtn->setGeometry(QRect(690, 90, 75, 23));
        rdbtnRawData = new QRadioButton(centralwidget);
        rdbtnRawData->setObjectName(QStringLiteral("rdbtnRawData"));
        rdbtnRawData->setGeometry(QRect(20, 30, 82, 17));
        rdbtnFiltData = new QRadioButton(centralwidget);
        rdbtnFiltData->setObjectName(QStringLiteral("rdbtnFiltData"));
        rdbtnFiltData->setGeometry(QRect(20, 70, 82, 17));
        rdbtnFFT = new QRadioButton(centralwidget);
        rdbtnFFT->setObjectName(QStringLiteral("rdbtnFFT"));
        rdbtnFFT->setGeometry(QRect(20, 110, 82, 17));
        widgetPlotZoom = new QCustomPlot(centralwidget);
        widgetPlotZoom->setObjectName(QStringLiteral("widgetPlotZoom"));
        widgetPlotZoom->setGeometry(QRect(130, 20, 761, 531));
        lineEditCutDataBeginWith = new QLineEdit(centralwidget);
        lineEditCutDataBeginWith->setObjectName(QStringLiteral("lineEditCutDataBeginWith"));
        lineEditCutDataBeginWith->setGeometry(QRect(50, 200, 61, 20));
        lineEditCutDataBeginWith->setStyleSheet(QStringLiteral("background-color: rgb(255, 122, 55);"));
        labelCutDataBeginWith = new QLabel(centralwidget);
        labelCutDataBeginWith->setObjectName(QStringLiteral("labelCutDataBeginWith"));
        labelCutDataBeginWith->setGeometry(QRect(20, 200, 31, 16));
        lineEditCutDataEndWith = new QLineEdit(centralwidget);
        lineEditCutDataEndWith->setObjectName(QStringLiteral("lineEditCutDataEndWith"));
        lineEditCutDataEndWith->setGeometry(QRect(50, 230, 61, 20));
        lineEditCutDataEndWith->setStyleSheet(QStringLiteral("background-color: rgb(255, 122, 55);"));
        labelCutDataEndWith = new QLabel(centralwidget);
        labelCutDataEndWith->setObjectName(QStringLiteral("labelCutDataEndWith"));
        labelCutDataEndWith->setGeometry(QRect(20, 230, 21, 16));
        btnCutData = new QPushButton(centralwidget);
        btnCutData->setObjectName(QStringLiteral("btnCutData"));
        btnCutData->setGeometry(QRect(20, 260, 41, 23));
        btnResetInput = new QPushButton(centralwidget);
        btnResetInput->setObjectName(QStringLiteral("btnResetInput"));
        btnResetInput->setGeometry(QRect(70, 260, 41, 23));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 927, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionClose);
        menuEdit->addAction(actionFeatures);
        menuEdit->addAction(actionReport);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        actionClose->setText(QApplication::translate("MainWindow", "Close", Q_NULLPTR));
        actionFeatures->setText(QApplication::translate("MainWindow", "Features", Q_NULLPTR));
        actionReport->setText(QApplication::translate("MainWindow", "Report", Q_NULLPTR));
        xAxisBtn->setText(QApplication::translate("MainWindow", "X Axis", Q_NULLPTR));
        yAxisBtn->setText(QApplication::translate("MainWindow", "Y Axis", Q_NULLPTR));
        zAxisBtn->setText(QApplication::translate("MainWindow", "Z Axis", Q_NULLPTR));
        resetBtn->setText(QApplication::translate("MainWindow", "Reset", Q_NULLPTR));
        oAxisBtn->setText(QApplication::translate("MainWindow", "O Axis", Q_NULLPTR));
        rdbtnRawData->setText(QApplication::translate("MainWindow", "Raw Data", Q_NULLPTR));
        rdbtnFiltData->setText(QApplication::translate("MainWindow", "Filt Data", Q_NULLPTR));
        rdbtnFFT->setText(QApplication::translate("MainWindow", "FFT", Q_NULLPTR));
        lineEditCutDataBeginWith->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        labelCutDataBeginWith->setText(QApplication::translate("MainWindow", "Begin", Q_NULLPTR));
        lineEditCutDataEndWith->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        labelCutDataEndWith->setText(QApplication::translate("MainWindow", "End", Q_NULLPTR));
        btnCutData->setText(QApplication::translate("MainWindow", "Cut", Q_NULLPTR));
        btnResetInput->setText(QApplication::translate("MainWindow", "Ret", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
