/********************************************************************************
** Form generated from reading UI file 'editwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITWINDOW_H
#define UI_EDITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editwindow
{
public:
    QTabWidget *tabWidget;
    QWidget *tabFeatures;
    QGroupBox *gboxTimeDomin;
    QLabel *labelMeanResult;
    QPushButton *btnMEAN;
    QLabel *labelVarResult;
    QPushButton *btnVAR;
    QLabel *labelMeanFormula;
    QPushButton *btnRMS;
    QLabel *labelRmsResult;
    QLabel *labelRmsFormula;
    QLabel *labelVarFormula;
    QLabel *labelStdDevFormula;
    QLabel *labelStdDevResult;
    QPushButton *btnStdDev;
    QTextEdit *textEditTimeDomain;
    QGroupBox *gboxFreqDomin;
    QLabel *labelResultFreqMean;
    QPushButton *btnFreqMean;
    QLabel *labelResultFreqPeak;
    QPushButton *btnFreqPeak;
    QLabel *labelFormulaFreqMean;
    QPushButton *btnSigPower;
    QLabel *labelResultSigPower;
    QLabel *labelFormulaSigPower;
    QLabel *labelFormulaFreqPeak;
    QLabel *labelFormulaSigEntropy;
    QLabel *labelResultSigEntropy;
    QPushButton *btnSigEntropy;
    QTextEdit *textEditFreqDomain;
    QWidget *tabReport;
    QPushButton *btnSaveFeatures;
    QPushButton *btnCalculate;
    QPushButton *btnClose;

    void setupUi(QWidget *editwindow)
    {
        if (editwindow->objectName().isEmpty())
            editwindow->setObjectName(QStringLiteral("editwindow"));
        editwindow->resize(816, 528);
        editwindow->setStyleSheet(QStringLiteral("background-color: rgb(176, 208, 255);"));
        tabWidget = new QTabWidget(editwindow);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(20, 20, 781, 491));
        tabFeatures = new QWidget();
        tabFeatures->setObjectName(QStringLiteral("tabFeatures"));
        gboxTimeDomin = new QGroupBox(tabFeatures);
        gboxTimeDomin->setObjectName(QStringLiteral("gboxTimeDomin"));
        gboxTimeDomin->setGeometry(QRect(10, 0, 761, 221));
        gboxTimeDomin->setStyleSheet(QLatin1String("background-color: rgb(148, 177, 255);\n"
"background-color: rgb(221, 239, 255);"));
        labelMeanResult = new QLabel(gboxTimeDomin);
        labelMeanResult->setObjectName(QStringLiteral("labelMeanResult"));
        labelMeanResult->setGeometry(QRect(120, 30, 61, 20));
        btnMEAN = new QPushButton(gboxTimeDomin);
        btnMEAN->setObjectName(QStringLiteral("btnMEAN"));
        btnMEAN->setGeometry(QRect(20, 30, 75, 23));
        labelVarResult = new QLabel(gboxTimeDomin);
        labelVarResult->setObjectName(QStringLiteral("labelVarResult"));
        labelVarResult->setGeometry(QRect(320, 30, 61, 20));
        btnVAR = new QPushButton(gboxTimeDomin);
        btnVAR->setObjectName(QStringLiteral("btnVAR"));
        btnVAR->setGeometry(QRect(220, 30, 75, 23));
        labelMeanFormula = new QLabel(gboxTimeDomin);
        labelMeanFormula->setObjectName(QStringLiteral("labelMeanFormula"));
        labelMeanFormula->setGeometry(QRect(20, 60, 161, 51));
        labelMeanFormula->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 255);"));
        btnRMS = new QPushButton(gboxTimeDomin);
        btnRMS->setObjectName(QStringLiteral("btnRMS"));
        btnRMS->setGeometry(QRect(20, 127, 75, 23));
        labelRmsResult = new QLabel(gboxTimeDomin);
        labelRmsResult->setObjectName(QStringLiteral("labelRmsResult"));
        labelRmsResult->setGeometry(QRect(120, 130, 61, 20));
        labelRmsFormula = new QLabel(gboxTimeDomin);
        labelRmsFormula->setObjectName(QStringLiteral("labelRmsFormula"));
        labelRmsFormula->setGeometry(QRect(20, 160, 161, 51));
        labelRmsFormula->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 255);"));
        labelVarFormula = new QLabel(gboxTimeDomin);
        labelVarFormula->setObjectName(QStringLiteral("labelVarFormula"));
        labelVarFormula->setGeometry(QRect(220, 60, 161, 51));
        labelVarFormula->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 255);"));
        labelStdDevFormula = new QLabel(gboxTimeDomin);
        labelStdDevFormula->setObjectName(QStringLiteral("labelStdDevFormula"));
        labelStdDevFormula->setGeometry(QRect(220, 160, 161, 51));
        labelStdDevFormula->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 255);"));
        labelStdDevResult = new QLabel(gboxTimeDomin);
        labelStdDevResult->setObjectName(QStringLiteral("labelStdDevResult"));
        labelStdDevResult->setGeometry(QRect(320, 130, 61, 20));
        btnStdDev = new QPushButton(gboxTimeDomin);
        btnStdDev->setObjectName(QStringLiteral("btnStdDev"));
        btnStdDev->setGeometry(QRect(220, 127, 75, 23));
        textEditTimeDomain = new QTextEdit(gboxTimeDomin);
        textEditTimeDomain->setObjectName(QStringLiteral("textEditTimeDomain"));
        textEditTimeDomain->setGeometry(QRect(410, 20, 341, 191));
        textEditTimeDomain->setStyleSheet(QStringLiteral("background-color: rgb(201, 255, 230);"));
        gboxFreqDomin = new QGroupBox(tabFeatures);
        gboxFreqDomin->setObjectName(QStringLiteral("gboxFreqDomin"));
        gboxFreqDomin->setGeometry(QRect(10, 240, 761, 221));
        gboxFreqDomin->setStyleSheet(QLatin1String("background-color: rgb(148, 177, 255);\n"
"background-color: rgb(221, 239, 255);"));
        labelResultFreqMean = new QLabel(gboxFreqDomin);
        labelResultFreqMean->setObjectName(QStringLiteral("labelResultFreqMean"));
        labelResultFreqMean->setGeometry(QRect(120, 30, 61, 20));
        btnFreqMean = new QPushButton(gboxFreqDomin);
        btnFreqMean->setObjectName(QStringLiteral("btnFreqMean"));
        btnFreqMean->setGeometry(QRect(20, 30, 75, 23));
        labelResultFreqPeak = new QLabel(gboxFreqDomin);
        labelResultFreqPeak->setObjectName(QStringLiteral("labelResultFreqPeak"));
        labelResultFreqPeak->setGeometry(QRect(320, 30, 61, 20));
        btnFreqPeak = new QPushButton(gboxFreqDomin);
        btnFreqPeak->setObjectName(QStringLiteral("btnFreqPeak"));
        btnFreqPeak->setGeometry(QRect(220, 30, 75, 23));
        labelFormulaFreqMean = new QLabel(gboxFreqDomin);
        labelFormulaFreqMean->setObjectName(QStringLiteral("labelFormulaFreqMean"));
        labelFormulaFreqMean->setGeometry(QRect(20, 60, 161, 51));
        labelFormulaFreqMean->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 255);"));
        btnSigPower = new QPushButton(gboxFreqDomin);
        btnSigPower->setObjectName(QStringLiteral("btnSigPower"));
        btnSigPower->setGeometry(QRect(20, 127, 75, 23));
        labelResultSigPower = new QLabel(gboxFreqDomin);
        labelResultSigPower->setObjectName(QStringLiteral("labelResultSigPower"));
        labelResultSigPower->setGeometry(QRect(120, 130, 61, 20));
        labelFormulaSigPower = new QLabel(gboxFreqDomin);
        labelFormulaSigPower->setObjectName(QStringLiteral("labelFormulaSigPower"));
        labelFormulaSigPower->setGeometry(QRect(20, 160, 161, 51));
        labelFormulaSigPower->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 255);"));
        labelFormulaFreqPeak = new QLabel(gboxFreqDomin);
        labelFormulaFreqPeak->setObjectName(QStringLiteral("labelFormulaFreqPeak"));
        labelFormulaFreqPeak->setGeometry(QRect(220, 60, 161, 51));
        labelFormulaFreqPeak->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 255);"));
        labelFormulaSigEntropy = new QLabel(gboxFreqDomin);
        labelFormulaSigEntropy->setObjectName(QStringLiteral("labelFormulaSigEntropy"));
        labelFormulaSigEntropy->setGeometry(QRect(220, 160, 161, 51));
        labelFormulaSigEntropy->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 255);"));
        labelResultSigEntropy = new QLabel(gboxFreqDomin);
        labelResultSigEntropy->setObjectName(QStringLiteral("labelResultSigEntropy"));
        labelResultSigEntropy->setGeometry(QRect(320, 130, 61, 20));
        btnSigEntropy = new QPushButton(gboxFreqDomin);
        btnSigEntropy->setObjectName(QStringLiteral("btnSigEntropy"));
        btnSigEntropy->setGeometry(QRect(220, 127, 75, 23));
        textEditFreqDomain = new QTextEdit(gboxFreqDomin);
        textEditFreqDomain->setObjectName(QStringLiteral("textEditFreqDomain"));
        textEditFreqDomain->setGeometry(QRect(410, 20, 341, 191));
        textEditFreqDomain->setStyleSheet(QStringLiteral("background-color: rgb(201, 255, 230);"));
        tabWidget->addTab(tabFeatures, QString());
        tabReport = new QWidget();
        tabReport->setObjectName(QStringLiteral("tabReport"));
        tabWidget->addTab(tabReport, QString());
        btnSaveFeatures = new QPushButton(editwindow);
        btnSaveFeatures->setObjectName(QStringLiteral("btnSaveFeatures"));
        btnSaveFeatures->setGeometry(QRect(610, 10, 75, 23));
        btnCalculate = new QPushButton(editwindow);
        btnCalculate->setObjectName(QStringLiteral("btnCalculate"));
        btnCalculate->setGeometry(QRect(500, 10, 75, 23));
        btnClose = new QPushButton(editwindow);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(390, 10, 75, 23));

        retranslateUi(editwindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(editwindow);
    } // setupUi

    void retranslateUi(QWidget *editwindow)
    {
        editwindow->setWindowTitle(QApplication::translate("editwindow", "Form", Q_NULLPTR));
        gboxTimeDomin->setTitle(QApplication::translate("editwindow", "Time Domain", Q_NULLPTR));
        labelMeanResult->setText(QApplication::translate("editwindow", "0.0", Q_NULLPTR));
        btnMEAN->setText(QApplication::translate("editwindow", "MEAN", Q_NULLPTR));
        labelVarResult->setText(QApplication::translate("editwindow", "0.0", Q_NULLPTR));
        btnVAR->setText(QApplication::translate("editwindow", "VAR", Q_NULLPTR));
        labelMeanFormula->setText(QString());
        btnRMS->setText(QApplication::translate("editwindow", "RMS", Q_NULLPTR));
        labelRmsResult->setText(QApplication::translate("editwindow", "0.0", Q_NULLPTR));
        labelRmsFormula->setText(QString());
        labelVarFormula->setText(QString());
        labelStdDevFormula->setText(QString());
        labelStdDevResult->setText(QApplication::translate("editwindow", "0.0", Q_NULLPTR));
        btnStdDev->setText(QApplication::translate("editwindow", "Std Dev", Q_NULLPTR));
        gboxFreqDomin->setTitle(QApplication::translate("editwindow", "Freq Domain", Q_NULLPTR));
        labelResultFreqMean->setText(QApplication::translate("editwindow", "0.0", Q_NULLPTR));
        btnFreqMean->setText(QApplication::translate("editwindow", "Freq Mean", Q_NULLPTR));
        labelResultFreqPeak->setText(QApplication::translate("editwindow", "0.0", Q_NULLPTR));
        btnFreqPeak->setText(QApplication::translate("editwindow", "Freq Peak", Q_NULLPTR));
        labelFormulaFreqMean->setText(QString());
        btnSigPower->setText(QApplication::translate("editwindow", "Sig Power", Q_NULLPTR));
        labelResultSigPower->setText(QApplication::translate("editwindow", "0.0", Q_NULLPTR));
        labelFormulaSigPower->setText(QString());
        labelFormulaFreqPeak->setText(QString());
        labelFormulaSigEntropy->setText(QString());
        labelResultSigEntropy->setText(QApplication::translate("editwindow", "0.0", Q_NULLPTR));
        btnSigEntropy->setText(QApplication::translate("editwindow", "Sig Entropy", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabFeatures), QApplication::translate("editwindow", "Features", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabReport), QApplication::translate("editwindow", "Report", Q_NULLPTR));
        btnSaveFeatures->setText(QApplication::translate("editwindow", "Save", Q_NULLPTR));
        btnCalculate->setText(QApplication::translate("editwindow", "Calculate", Q_NULLPTR));
        btnClose->setText(QApplication::translate("editwindow", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class editwindow: public Ui_editwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITWINDOW_H
