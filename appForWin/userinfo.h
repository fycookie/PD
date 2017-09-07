#ifndef USERINFO_H
#define USERINFO_H

#include <string>
#include "QtSql/QSqlDatabase"
#include  <QVariant>

using namespace std;

class UserInfo
{
public:
    explicit UserInfo();
    ~UserInfo() {}
    bool IsRegistered(QString userName);
    bool IsChecked(QString userName, QString password);

public:
    void DeleteUser();
    void AddUser(QString userName, QString password);

private:
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    void CloseDatabase();
    bool OpenDatabase();
};

#endif // USERINFO_H
