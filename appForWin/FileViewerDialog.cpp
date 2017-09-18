#include "FileViewerDialog.h"
#include <QVBoxLayout>

FileViewerDialog::FileViewerDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("File Viewer"));
    currDir = new QLineEdit;
    currDir->setText("E://");
    fileListWidget =new QListWidget;
    QVBoxLayout *vbLayout=new QVBoxLayout(this);
    vbLayout->addWidget(currDir);
    vbLayout->addWidget(fileListWidget);

    connect(currDir,SIGNAL(returnPressed()),this,SLOT(ShowFiles()));
    connect(fileListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this,SLOT(ShowDir(QListWidgetItem*)));

    QString root="E://";
    QDir rootDir(root);

    QStringList strings;
    strings<<"*";
    QFileInfoList list=rootDir.entryInfoList(strings);
    ShowFileInfoList(list);
}

FileViewerDialog::~FileViewerDialog()
{

}

void FileViewerDialog::ShowFileInfoList(QFileInfoList list)
{
    fileListWidget->clear();
    for(int i=0;i<list.count();i++)
    {
        QFileInfo tmpFileInfo=list.at(i);
        if((tmpFileInfo.isDir()))
        {
            QIcon icon(":/images/dir.png");
            QString fileName=tmpFileInfo.fileName();
            QListWidgetItem *tmp=new QListWidgetItem(icon,fileName);
            fileListWidget->addItem(tmp);
        }
        else if(tmpFileInfo.isFile())
        {
            QIcon icon(":/image/file.png");
            QString fileName=tmpFileInfo.fileName();
            QListWidgetItem *tmp=new QListWidgetItem(icon,fileName);
            fileListWidget->addItem(tmp);
        }
    }
}

void FileViewerDialog::ShowDir(QListWidgetItem *item)
{
    QString str=item->text();
    QDir dir;
    dir.setPath(currDir->text()); //set dir
    dir.cd(str);
    currDir->setText(dir.absolutePath());
    ShowFiles(dir);
}

void::FileViewerDialog::ShowFiles(QDir dir)
{
    QStringList strings;
    strings<<"*";
    //文件名称过滤器
    //文件属性过滤器，目录，文件，读写
    //排序方式，名称，修改时间，大小，目录优先
    QFileInfoList list = dir.entryInfoList(strings,
        QDir::AllEntries,
        QDir::DirsFirst);
    ShowFileInfoList(list);
}

void FileViewerDialog::ShowFiles()
{
    QDir dir(currDir->text());
    ShowFiles(dir);
}




























































