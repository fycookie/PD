/********************************************************************************
** Form generated from reading UI file 'RegisterDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *passwordLabel;
    QLineEdit *passwordLine;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *retypePsdLabel;
    QLineEdit *retypePsdLine;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *checkCodeLabel;
    QLineEdit *checkCodeLine;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *userNameLabel;
    QLineEdit *userNameLine;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *registerbtn;
    QPushButton *returnbtn;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName(QStringLiteral("RegisterDialog"));
        RegisterDialog->resize(400, 300);
        label = new QLabel(RegisterDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(150, 30, 161, 41));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setMidLineWidth(0);
        layoutWidget = new QWidget(RegisterDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(120, 120, 209, 22));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        passwordLabel = new QLabel(layoutWidget);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        passwordLabel->setFont(font1);

        horizontalLayout_2->addWidget(passwordLabel);

        passwordLine = new QLineEdit(layoutWidget);
        passwordLine->setObjectName(QStringLiteral("passwordLine"));

        horizontalLayout_2->addWidget(passwordLine);

        layoutWidget_2 = new QWidget(RegisterDialog);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(120, 160, 209, 22));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        retypePsdLabel = new QLabel(layoutWidget_2);
        retypePsdLabel->setObjectName(QStringLiteral("retypePsdLabel"));
        retypePsdLabel->setFont(font1);

        horizontalLayout_3->addWidget(retypePsdLabel);

        retypePsdLine = new QLineEdit(layoutWidget_2);
        retypePsdLine->setObjectName(QStringLiteral("retypePsdLine"));

        horizontalLayout_3->addWidget(retypePsdLine);

        layoutWidget_3 = new QWidget(RegisterDialog);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(120, 200, 209, 22));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        checkCodeLabel = new QLabel(layoutWidget_3);
        checkCodeLabel->setObjectName(QStringLiteral("checkCodeLabel"));
        checkCodeLabel->setFont(font1);

        horizontalLayout_4->addWidget(checkCodeLabel);

        checkCodeLine = new QLineEdit(layoutWidget_3);
        checkCodeLine->setObjectName(QStringLiteral("checkCodeLine"));

        horizontalLayout_4->addWidget(checkCodeLine);

        layoutWidget1 = new QWidget(RegisterDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(120, 80, 209, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        userNameLabel = new QLabel(layoutWidget1);
        userNameLabel->setObjectName(QStringLiteral("userNameLabel"));
        userNameLabel->setFont(font1);

        horizontalLayout->addWidget(userNameLabel);

        userNameLine = new QLineEdit(layoutWidget1);
        userNameLine->setObjectName(QStringLiteral("userNameLine"));

        horizontalLayout->addWidget(userNameLine);

        layoutWidget2 = new QWidget(RegisterDialog);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(150, 240, 158, 25));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        registerbtn = new QPushButton(layoutWidget2);
        registerbtn->setObjectName(QStringLiteral("registerbtn"));

        horizontalLayout_5->addWidget(registerbtn);

        returnbtn = new QPushButton(layoutWidget2);
        returnbtn->setObjectName(QStringLiteral("returnbtn"));

        horizontalLayout_5->addWidget(returnbtn);


        retranslateUi(RegisterDialog);

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QApplication::translate("RegisterDialog", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("RegisterDialog", "User Register", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("RegisterDialog", "  Password", Q_NULLPTR));
        retypePsdLabel->setText(QApplication::translate("RegisterDialog", "RetypePsd", Q_NULLPTR));
        checkCodeLabel->setText(QApplication::translate("RegisterDialog", "Check  Label", Q_NULLPTR));
        userNameLabel->setText(QApplication::translate("RegisterDialog", " User Name", Q_NULLPTR));
        registerbtn->setText(QApplication::translate("RegisterDialog", "Register", Q_NULLPTR));
        returnbtn->setText(QApplication::translate("RegisterDialog", "Return", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
