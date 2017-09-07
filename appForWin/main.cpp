#include "LoginDialog.h"
#include <QApplication>
#include <QIcon>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QMessageBox>
#include "UserInfo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
//    qDebug()<<"ODBC driver?" << db.isValid();
//    QString dsn = QString::fromLocal8Bit("cookie32bit");
//    db.setDatabaseName(dsn);
//    db.setHostName("localhost");
//    db.setUserName("sa");
//    db.setPassword("yFANG9170");
//    db.setPort(1433);
//    if(db.open())
//    {
//        QMessageBox::information(NULL, "Hint", "connect sql server successfully!", QMessageBox::Yes);
//        LoginDialog w;
//        w.show();
//        db.close();
//        return a.exec();
//    }
//    else
//    {
//        qDebug()<<db.lastError();
//        QMessageBox::information(NULL, "Warnning", "connect sql server failed!", QMessageBox::Yes);
//    }
    LoginDialog w;
    w.show();
    return a.exec();
}
