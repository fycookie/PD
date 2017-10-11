#-------------------------------------------------
#
# Project created by QtCreator 2017-07-16T19:23:23
#
#-------------------------------------------------

QT       += core gui

QT += sql

QT += widgets printsupport

QT += axcontainer

TARGET = data
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    LoginDialog.cpp \
    UserInfo.cpp \
    MainWindow.cpp \
    qcustomplot.cpp \
    cfft.cpp \
    editwindow.cpp \
    RegisterDialog.cpp \
    knn.cpp

HEADERS += \
    LoginDialog.h \
    RegisterDialog.h \
    UserInfo.h \
    MainWindow.h \
    qcustomplot.h \
    FirCoeff.h \
    editwindow.h \
    cfft.h \
    complex.h \
    common.h \
    knn.h

FORMS += \
    LoginDialog.ui \
    RegisterDialog.ui \
    mainwindow.ui \
    editwindow.ui

DISTFILES += \
    icon/mean_formula.png \
    icon/rms_formula.png \
    icon/standard_formula.png \
    icon/var_formula.png \
    icon/login_map.jpg \
    icon/mainwindow_map.jpg
