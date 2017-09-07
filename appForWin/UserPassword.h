#ifndef USERPASSWORD_H
#define USERPASSWORD_H

#include <QWidget>
#include <QDebug>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QTime>
#include <QMessageBox>
namespace Ui {
class UserPassWord;
}

class UserPassWord : public QWidget
{
    Q_OBJECT

public:
    explicit UserPassWord(QWidget *parent = 0);
    ~UserPassWord();
    void setyf();
    void clearAll();
    bool judgeEmpty();
private:
    Ui::UserPassWord *ui;
    QString teachernum;
    int yf;
    QSqlTableModel *model;

private slots:
    void comeDataManage(QString);
    void confirmbtnSlot();
    void returnbtnSlot();
signals:
    void EmitToUserManage();
};

#endif // USERPASSWORD_H
