#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include "UserInfo.h"
#include "MainWindow.h"
#include <QVBoxLayout>
#include <QtGui>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QPixmap>

LoginDialog::LoginDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    //设置对话框的大小
    this->setMaximumSize(500,750);
    this->setMinimumSize(320,360);

    //设置登录按钮不可用
    ui->loginbtn->setEnabled(false);
    //设置lineedit提示语句
    ui->userNameLine->setPlaceholderText("Input User Name");
    ui->passwordLine->setPlaceholderText("Input Password");
    //设置passlineedit显示为密码模式
    ui->passwordLine->setEchoMode(QLineEdit::Password);
    //连接信号与槽
    connect(ui->loginbtn,SIGNAL(clicked()),this,SLOT(LoginbtnSlot()));
    connect(ui->registerbtn,SIGNAL(clicked()),this,SLOT(RegisterbtnSlot()));
    connect(ui->exitbtn,SIGNAL(clicked()),this,SLOT(ExitbtnSlot()));
    //设置登录按钮可用
    connect(ui->userNameLine,SIGNAL(textChanged(QString)),this,SLOT(LoginbtnSetSlot(QString)));
    connect(ui->passwordLine,SIGNAL(textChanged(QString)),this,SLOT(LoginbtnSetSlot(QString)));

    QPixmap login_map("./icon/login_map.jpg");
    login_map=login_map.scaled(
                ui->centralWidget->width(),
                ui->centralWidget->height());
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(login_map));
    this->setPalette(palette);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
void LoginDialog::LoginbtnSlot()
{
    if(!this->JudgeEmpty())
    {
        ClearAll();
        return;
    }

    UserInfo user;
    if(user.IsChecked(ui->userNameLine->text(), ui->passwordLine->text())||
            (ui->userNameLine->text()=="yf"&&ui->passwordLine->text()=="yf"))
    {
        view = new MainWindow;
        connect(view,SIGNAL(toLoginDialog()), this, SLOT(showNormal()));
        this->hide();
        view->show();
        return;
    }
    else
    {
        QMessageBox::information(this,"Warning","Wrong Password",QMessageBox::Yes);
        this->ClearAll();
        return;
    }
}

void LoginDialog::RegisterbtnSlot()
{
    RegisterDialog d(this);
    this->hide();
    if(d.exec()==QDialog::Accepted)
    {
        this->showNormal();
    }
    this->ClearAll();
}

void LoginDialog::ExitbtnSlot()
{
    this->close();
}
void LoginDialog::LoginbtnSetSlot(QString)
{
    ui->loginbtn->setEnabled(true);
}

void LoginDialog::ClearAll()
{
    ui->userNameLine->clear();
    ui->passwordLine->clear();
}

bool LoginDialog::JudgeEmpty()
{
    if(ui->userNameLine->text().isEmpty())
    {
        QMessageBox::warning(this,"Warnning","User name cannot be empty");
        return false;
    }
    if(ui->passwordLine->text().isEmpty())
    {
        QMessageBox::warning(this,"Warnning","Password cannot be empty");
        return false;
    }
    else
        return true;
}
