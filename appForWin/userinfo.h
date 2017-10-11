#ifndef USERINFO_H
#define USERINFO_H

#include <string>
#include "QtSql/QSqlDatabase"
#include  <QVariant>
#include "common.h"

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

//以下均为特征值的相关内容
private:
    Features features;
    vector<Features> VectorFeatures;

public:
    void FeaturesTrans(vector<Features> *vec);
    void AddFeatures(Features *data);
    void LoadFeatures(vector<Features> *vec);
};

#endif // USERINFO_H
