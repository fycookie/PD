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
    QCustomPlot *widgetPlotZoom;
    QRadioButton *rdbtnRawData;
    QRadioButton *rdbtnFiltData;
    QRadioButton *rdbtnFFT;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        widgetplotX = new QCustomPlot(centralwidget);
        widgetplotX->setObjectName(QStringLiteral("widgetplotX"));
        widgetplotX->setGeometry(QRect(130, 20, 571, 81));
        xAxisBtn = new QPushButton(widgetplotX);
        xAxisBtn->setObjectName(QStringLiteral("xAxisBtn"));
        xAxisBtn->setGeometry(QRect(500, 60, 75, 23));
        widgetplotY = new QCustomPlot(centralwidget);
        widgetplotY->setObjectName(QStringLiteral("widgetplotY"));
        widgetplotY->setGeometry(QRect(130, 130, 571, 81));
        yAxisBtn = new QPushButton(widgetplotY);
        yAxisBtn->setObjectName(QStringLiteral("yAxisBtn"));
        yAxisBtn->setGeometry(QRect(500, 60, 75, 23));
        widgetplotZ = new QCustomPlot(centralwidget);
        widgetplotZ->setObjectName(QStringLiteral("widgetplotZ"));
        widgetplotZ->setGeometry(QRect(130, 240, 571, 81));
        zAxisBtn = new QPushButton(widgetplotZ);
        zAxisBtn->setObjectName(QStringLiteral("zAxisBtn"));
        zAxisBtn->setGeometry(QRect(500, 60, 75, 23));
        resetBtn = new QPushButton(centralwidget);
        resetBtn->setObjectName(QStringLiteral("resetBtn"));
        resetBtn->setGeometry(QRect(20, 150, 75, 23));
        widgetplotO = new QCustomPlot(centralwidget);
        widgetplotO->setObjectName(QStringLiteral("widgetplotO"));
        widgetplotO->setGeometry(QRect(130, 350, 571, 81));
        oAxisBtn = new QPushButton(widgetplotO);
        oAxisBtn->setObjectName(QStringLiteral("oAxisBtn"));
        oAxisBtn->setGeometry(QRect(500, 60, 75, 23));
        widgetPlotZoom = new QCustomPlot(centralwidget);
        widgetPlotZoom->setObjectName(QStringLiteral("widgetPlotZoom"));
        widgetPlotZoom->setGeometry(QRect(130, 19, 571, 411));
        rdbtnRawData = new QRadioButton(centralwidget);
        rdbtnRawData->setObjectName(QStringLiteral("rdbtnRawData"));
        rdbtnRawData->setGeometry(QRect(20, 30, 82, 17));
        rdbtnFiltData = new QRadioButton(centralwidget);
        rdbtnFiltData->setObjectName(QStringLiteral("rdbtnFiltData"));
        rdbtnFiltData->setGeometry(QRect(20, 70, 82, 17));
        rdbtnFFT = new QRadioButton(centralwidget);
        rdbtnFFT->setObjectName(QStringLiteral("rdbtnFFT"));
        rdbtnFFT->setGeometry(QRect(20, 110, 82, 17));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionClose);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        actionClose->setText(QApplication::translate("MainWindow", "Close", Q_NULLPTR));
        xAxisBtn->setText(QApplication::translate("MainWindow", "X Axis", Q_NULLPTR));
        yAxisBtn->setText(QApplication::translate("MainWindow", "Y Axis", Q_NULLPTR));
        zAxisBtn->setText(QApplication::translate("MainWindow", "Z Axis", Q_NULLPTR));
        resetBtn->setText(QApplication::translate("MainWindow", "Reset", Q_NULLPTR));
        oAxisBtn->setText(QApplication::translate("MainWindow", "O Axis", Q_NULLPTR));
        rdbtnRawData->setText(QApplication::translate("MainWindow", "Raw Data", Q_NULLPTR));
        rdbtnFiltData->setText(QApplication::translate("MainWindow", "Filt Data", Q_NULLPTR));
        rdbtnFFT->setText(QApplication::translate("MainWindow", "FFT", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
