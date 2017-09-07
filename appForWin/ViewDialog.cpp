#include "ViewDialog.h"
#include "ui_ViewDialog.h"

ViewDialog::ViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDialog)
{
    ui->setupUi(this);
    //设置对话框的大小
    this->setMaximumSize(1000,800);
    this->setMinimumSize(500,400);
}
