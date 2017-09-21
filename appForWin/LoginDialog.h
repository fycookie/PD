#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "RegisterDialog.h"
#include <QDebug>
#include <QDialog>
#include <QPalette>
#include <QButtonGroup>
#include <QMessageBox>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QtGui/QApplicationStateChangeEvent>
#include "MainWindow.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void ClearAll();
    bool JudgeEmpty();
private:
    Ui::LoginDialog *ui;
    MainWindow *view;
private slots:
    void ExitbtnSlot();
    void RegisterbtnSlot();
    void LoginbtnSlot();
    void LoginbtnSetSlot(QString);
};

#endif // LOGINDIALOG_H
