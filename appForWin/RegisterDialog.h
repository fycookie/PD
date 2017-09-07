#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QPalette>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QTime>
#include <QMessageBox>
#include <QButtonGroup>
namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = 0);
    ~RegisterDialog();
    void SetCheckCode();
    bool JudgeEmpty();
private:
    Ui::RegisterDialog *ui;
    QSqlTableModel *user;
    int checkCode;
private slots:
    void ReturnbtnSlot();
    void RegisterbtnSetSlot();
    void TextChanged();
private:
    //bool IsRegistered();
    void ClearAll();
    bool InfoCheck();
};

#endif // REGISTERDIALOG_H
