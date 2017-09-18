#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"
#include "UserInfo.h"
#include <QtGui>

RegisterDialog::RegisterDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    //设置对话框的大小
    this->setMaximumSize(500,750);
    this->setMinimumSize(320,400);
    //创建model,进行数据库操作
    user=new QSqlTableModel(this);
    user->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //设置两行密码lineedit的显示
    ui->passwordLine->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ui->retypePsdLine->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    //设置lineedit提示语句
    ui->userNameLine->setPlaceholderText("请输入用户名");
    ui->passwordLine->setPlaceholderText("请输入密码");
    ui->retypePsdLine->setPlaceholderText("请重新输入密码");
    ui->checkCodeLine->setPlaceholderText("请输入验证码");
    //设置注册按钮不可用
    ui->registerbtn->setEnabled(false);

    //设置验证码
    this->SetCheckCode();

    //line edit与槽连接
    connect(ui->registerbtn,SIGNAL(clicked()),this,SLOT(RegisterbtnSetSlot()));
    connect(ui->returnbtn,SIGNAL(clicked()),this,SLOT(ReturnbtnSlot()));
    connect(ui->userNameLine,SIGNAL(textChanged(QString)),this,SLOT(TextChanged()));
}

void RegisterDialog::TextChanged()
{
    ui->registerbtn->setEnabled(true);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::ClearAll()
{
    ui->passwordLine->clear();
    ui->retypePsdLine->clear();
    ui->checkCodeLine->clear();
}

bool RegisterDialog::InfoCheck()
{
    //判断lineEdit是否为空
    if(!this->JudgeEmpty())
    {
        ClearAll();
        return false;
    }
    //判断两次密码输入是否一致
    if(ui->passwordLine->text()!= ui->retypePsdLine->text())
    {
        QMessageBox::warning(this,"Warning","Two password are different.",QMessageBox::Yes);
        ClearAll();
        this->SetCheckCode();
        return false;
    }
    //判断验证码输入是否正确
    if(ui->checkCodeLine->text()!= ui->checkCodeLabel->text())
    {
        QMessageBox::warning(this,"Warning","Check code wrong",QMessageBox::Yes);
        ClearAll();
        this->SetCheckCode();
        return false;
    }

    QMessageBox::warning(this,"Hint","Pass check",QMessageBox::Yes);
    return true;
}

void RegisterDialog::ReturnbtnSlot()
{
    this->accept();
}

void RegisterDialog::RegisterbtnSetSlot()
{
    if(InfoCheck())
    {
        UserInfo user;
        ui->registerbtn->setEnabled(true);
        user.AddUser(ui->userNameLine->text(), ui->passwordLine->text());
        ReturnbtnSlot();
    }
}

//设置验证码
void RegisterDialog::SetCheckCode()
{
    QPalette p1;
    p1.setColor(QPalette::WindowText,Qt::red);
    checkCode=qrand()%10000;
    while(checkCode<1000)
        checkCode=qrand()%10000;
    ui->checkCodeLabel->setText(QString::number(checkCode));
    ui->checkCodeLabel->setPalette(p1);
}

//判断line edit是否为空
bool RegisterDialog::JudgeEmpty()
{
    if(ui->userNameLine->text().isEmpty())
    {
        QMessageBox::warning(this,"Warning","User name cannot be empty");
        return false;
    }

    else if(ui->passwordLine->text().isEmpty()||
            ui->retypePsdLine->text().isEmpty())
    {
        QMessageBox::warning(this,"Warning","User password cannot be empty");
        return false;
    }

    else if(ui->checkCodeLine->text().isEmpty())
    {
        QMessageBox::warning(this,"Warning","Check code cannot be empty");
        return false;
    }\

    else
        return true;
}


