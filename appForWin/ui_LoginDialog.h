/********************************************************************************
** Form generated from reading UI file 'LoginDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *loginbtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *registerbtn;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *exitbtn;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *userNameLabel;
    QLineEdit *userNameLine;
    QHBoxLayout *horizontalLayout_2;
    QLabel *passwordLabel;
    QLineEdit *passwordLine;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(400, 300);
        centralWidget = new QWidget(LoginDialog);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setGeometry(QRect(0, 0, 337, 236));
        centralWidget->setStyleSheet(QStringLiteral("./icon/login_map.jpg"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 40, 241, 41));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 170, 277, 26));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        loginbtn = new QPushButton(layoutWidget);
        loginbtn->setObjectName(QStringLiteral("loginbtn"));
        QFont font1;
        font1.setPointSize(10);
        loginbtn->setFont(font1);
        loginbtn->setAutoDefault(true);

        horizontalLayout_3->addWidget(loginbtn);

        horizontalSpacer = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        registerbtn = new QPushButton(layoutWidget);
        registerbtn->setObjectName(QStringLiteral("registerbtn"));
        registerbtn->setFont(font1);
        registerbtn->setAutoDefault(true);

        horizontalLayout_3->addWidget(registerbtn);

        horizontalSpacer_2 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        exitbtn = new QPushButton(layoutWidget);
        exitbtn->setObjectName(QStringLiteral("exitbtn"));
        exitbtn->setFont(font1);
        exitbtn->setAutoDefault(true);

        horizontalLayout_3->addWidget(exitbtn);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(60, 100, 222, 52));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        userNameLabel = new QLabel(layoutWidget1);
        userNameLabel->setObjectName(QStringLiteral("userNameLabel"));
        QFont font2;
        font2.setFamily(QStringLiteral("Times New Roman"));
        font2.setPointSize(12);
        userNameLabel->setFont(font2);

        horizontalLayout->addWidget(userNameLabel);

        userNameLine = new QLineEdit(layoutWidget1);
        userNameLine->setObjectName(QStringLiteral("userNameLine"));

        horizontalLayout->addWidget(userNameLine);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        passwordLabel = new QLabel(layoutWidget1);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));
        passwordLabel->setFont(font2);

        horizontalLayout_2->addWidget(passwordLabel);

        passwordLine = new QLineEdit(layoutWidget1);
        passwordLine->setObjectName(QStringLiteral("passwordLine"));

        horizontalLayout_2->addWidget(passwordLine);


        verticalLayout->addLayout(horizontalLayout_2);

        menuBar = new QMenuBar(LoginDialog);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        mainToolBar = new QToolBar(LoginDialog);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setGeometry(QRect(0, 0, 4, 12));
        statusBar = new QStatusBar(LoginDialog);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setGeometry(QRect(0, 0, 3, 18));
        QFont font3;
        font3.setFamily(QStringLiteral("Times New Roman"));
        font3.setPointSize(16);
        font3.setBold(true);
        font3.setWeight(75);
        statusBar->setFont(font3);

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "LoginDialog", Q_NULLPTR));
        label->setText(QApplication::translate("LoginDialog", "PD Tremer Analysis", Q_NULLPTR));
        loginbtn->setText(QApplication::translate("LoginDialog", "Login", Q_NULLPTR));
        registerbtn->setText(QApplication::translate("LoginDialog", "Register", Q_NULLPTR));
        exitbtn->setText(QApplication::translate("LoginDialog", "Exit", Q_NULLPTR));
        userNameLabel->setText(QApplication::translate("LoginDialog", "User Name :", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("LoginDialog", "  Password : ", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
