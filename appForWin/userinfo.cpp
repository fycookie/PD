#include "UserInfo.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include <QMessageBox>
#include <QVariant>
#include <QVariantList>
#include <QDebug>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlTableModel>
#include <iostream>
#include <QDateTime>
#include <vector>

UserInfo::UserInfo()
{
    //this->userName = user;
    //this->password = pwd;
}

void UserInfo::CloseDatabase()
{
    if(db.isOpen())
        db.close();
}

bool UserInfo::OpenDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    qDebug()<<"ODBC driver?" << db.isValid();
    QString dsn = QString::fromLocal8Bit("cookie32bit");
    db.setDatabaseName(dsn);
    db.setHostName("localhost");
    db.setUserName("sa");
    db.setPassword("yFANG9170");
    db.setPort(1433);
    if(!db.open())
    {
        qDebug()<<"connect sql server failed!";
        //QMessageBox::information(NULL, "Warnning", "connect sql server failed!", QMessageBox::Yes);
        return false;
    }
    else
    {
        qDebug()<<"connect sql server successfully!";
        //QMessageBox::information(NULL, "Hint", "connect sql server successfully!", QMessageBox::Yes);
        return true;
    }
}

bool UserInfo::IsRegistered(QString userName)
{
//    if(!OpenDatabase())
//    {
//        qDebug()<<"IsRegistered of OpenDatabase: false";
//        return false;
//    }

//    QSqlQuery query;
//    QString str, result;
//    str = QString("SELECT uName FROM PDUser WHERE uName = %1").arg(userName);
//    query.exec(str);
//    result=query.value(1).toString();
//    qDebug()<<"result: " <<result;
//    if(query.isSelect())
//    {
//        qDebug()<<"user exist.";
//        return true;
//    }
//    else
//    {
//        qDebug()<<"user not exist.";
//        return false;
//    }

//    CloseDatabase();
    return true;
}

bool UserInfo::IsChecked(QString userName, QString password)
{
    OpenDatabase();
    QSqlTableModel model;
    model.setTable("PDUser");
    model.select();
    for(int i=0; i<model.rowCount(); i++)
    {
        QSqlRecord record = model.record(i);
        if(record.value(0)==userName &&
                record.value(1)==password)
        {
            QMessageBox::information(NULL, "Hint", userName+" login successfully.",
                                     QMessageBox::Yes);
            CloseDatabase();
            return true;
        }
        if(record.value(0)==userName &&
                record.value(1)!=password)
        {
            QMessageBox::information(NULL, "Hint", userName+" password wrong, try again.",
                                     QMessageBox::Yes);
            CloseDatabase();
            return false;
        }
    }
    CloseDatabase();
    qDebug()<<"Cannot find user";
    return false;
}


//    QString str = QString("SELECT uPswd FROM PDUser WHERE uName = %1").arg(userName);
//    QSqlQuery query;
//    query.exec(str);
//    QSqlRecord record = query.record();
//    QString pwd=record.value("uPswd").toString();

//    str=query.value(0).toString();

//    qDebug()<<"result: " <<query.result();
//    qDebug()<<"value(0): " <<query.value(0);
//    qDebug()<<"record(0): " <<query.boundValue(0).toString();

//    if(query.value(0) == password)
//    {
//        qDebug()<<"result: " <<query.result();
//        return true;
//    }
//    else
//    {
//        qDebug()<<"check fail";
//        return false;
//    }
//}

void UserInfo::AddUser(QString userName, QString password)
{
    if(!OpenDatabase())
        return;

    QSqlQuery q;
    QString ss;
    ss="select *from sys.tables where name='PDUser'";
    q.exec(ss);
    if(!q.next())
    {
        qDebug()<<"table not exsit.";
        CloseDatabase();
        return;
    }
    else
    {
         qDebug()<<"yes, it exist.";
    }

    QString insert;
    //sprintf(insert,"insert into PDUser(userName,password) values('%s','%s')",u,p);
    //insert = "insert into PDUser(userName,password) values('{0}','{1}')";
    //insert = "insert into PDUser(userName,password) values('+u+','+p+')";
    //insert = ("insert into PDUser(userName,password) values('%s','%s')",u,p);
    //insert = "insert into PDUser(userName,password) values('"+ u +","+ p +"')";
    insert = QString("insert into PDUser(uName,upswd) values('%1','%2')").arg(userName).arg(password);
    QSqlQuery query;
    query.exec(insert);
    if(query.numRowsAffected() > 0)
    {
        qDebug()<<"Add successfully";
    }
    else
    {
        qDebug()<<"Add fail";
    }
//    if(query.next())
//    {
//        QMessageBox::information(NULL, "Hint", "Add ser successfully!", QMessageBox::Yes);
//    }
//    else
//    {
//        qDebug()<<query.lastQuery();
//        QMessageBox::information(NULL, "Hint", "Add user failure!", QMessageBox::Yes);
//    }
//    query.bindValue(u, p);
//    QSqlQuery query("INSERT INTO PDUser(userName, password)VALUES(:userName, :password)");
//    query.bindValue(u, p);
//    if(query.lastInsertId() != 0)
//    {
//        QMessageBox::information(NULL, "Hint", "Add ser successfully!", QMessageBox::Yes);
//    }
//    else
//    {
//        qDebug()<<query.lastInsertId();
//        qDebug()<<query.lastQuery();
//        QMessageBox::information(NULL, "Hint", "Add user failure!", QMessageBox::Yes);
//    }

    CloseDatabase();
}

void UserInfo::DeleteUser()
{
//    if(!IsRegistered())
//    {
//        QMessageBox::information(NULL, "Warnning", "User dose not exist!", QMessageBox::Yes);
//        return;
//    }

//    QSqlQuery query("DELETE FROM PDUser WHERE userName = this->Users.userName");
//    query.exec();
}

//void UserInfo::AddFeatures(Features data)
//{
//    if(!OpenDatabase())
//        return;

//    QSqlQuery query;
//    QString str;
//    str="select *from sys.tables where name='PDFeatures'";
//    query.exec(str);
//    if(!query.next())
//    {
//        qDebug()<<"table not exsit.";
//        CloseDatabase();
//        return;
//    }
//    else
//    {
//         qDebug()<<"yes, it exist.";
//    }

//    QSqlQuery qInsert;
//    qInsert.prepare("insert into PDFeatures values("
//                    "?,?,?,?,?,?,?,?,?)");
//    QDataStream ins;
//    //ins.append(data.datetime);
//    ins>>data.datetime>>data.MEAN>>data.RMS>>
//         data.VAR>>data.StdDev>>data.FreqMean>>
//         data.SigPower>>data.SigEntropy;

//    qInsert.addBindValue(ins);

//    int reg=query.numRowsAffected();
//    if(reg > 0)
//    {
//        qDebug()<<"Add successfully: "<<reg;
//    }
//    else
//    {
//        qDebug()<<"Add fail";
//    }

//    CloseDatabase();
//}

void UserInfo::AddFeatures(Features *data)
{
    if(!OpenDatabase())
        return;

    QSqlTableModel model;
    model.setTable("PDFeatures");
    int reg1=model.rowCount();
    data->datetime=QDateTime::currentDateTime().toString(
                "yyyy-MM-dd hh:mm:ss");
    QSqlRecord record=model.record();
    record.setValue("DateAndTime",data->datetime);
    record.setValue("MeanAmp",data->MEAN);
    record.setValue("RootMeanSqure",data->RMS);
    record.setValue("StdDev",data->StdDev);
    record.setValue("Variance",data->VAR);
    record.setValue("FreqPeak",data->FreqMean);
    record.setValue("FreqMean",data->FreqPeak);
    record.setValue("SigPower",data->SigPower);
    record.setValue("SigEntropy",data->SigEntropy);
    model.insertRecord(-1,record);
    model.submitAll();

    int reg2=model.rowCount();
    if(reg2-reg1 > 0)
    {
        QMessageBox::information(NULL, "Hint",
              "Save successfully!",QMessageBox::Yes);
//        qDebug()<<"Add successfully: "<<reg2-reg1;
    }
    else
    {
        qDebug()<<"Add fail";
    }

    //CloseDatabase();
}

//void UserInfo::FeaturesTrans(vector<Features> *vec)
//{
//    if(LoadFeatures()>0)
//    {
//        for(auto item:VectorFeatures)
//            vec->push_back(item);
//    }
//}

void UserInfo::LoadFeatures(vector<Features> *vec)
{
    OpenDatabase();
    QSqlTableModel model;
    model.setTable("PDFeatures");
    model.select();
    for(int i=0; i<model.rowCount(); i++)
    {
        QSqlRecord record = model.record(i);
        if(record.value(1)==0.0 && record.value(2)==0.0
                &&record.value(3)==0.0 && record.value(4)==0.0
                &&record.value(5)==0.0 && record.value(6)==0.0
                &&record.value(7)==0.0 &&record.value(8)==0.0)
        {
            CloseDatabase();
            qDebug()<<"Cannot find user";
            return;
        }
        else
        {
            Features featuresNew;
            featuresNew.datetime=record.value(0).toString();
            featuresNew.MEAN=record.value(1).toDouble();
            featuresNew.RMS=record.value(2).toDouble();
            featuresNew.VAR=record.value(3).toDouble();
            featuresNew.StdDev=record.value(4).toDouble();
            featuresNew.FreqMean=record.value(5).toDouble();
            featuresNew.FreqPeak=record.value(6).toDouble();
            featuresNew.SigPower=record.value(7).toDouble();
            featuresNew.SigEntropy=record.value(8).toDouble();
            vec->push_back(featuresNew);
        }
    }

    //CloseDatabase();
    //return VectorFeatures.size();
}
