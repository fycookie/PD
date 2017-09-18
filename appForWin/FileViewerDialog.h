#ifndef FILEVIEWERDIALOG_H
#define FILEVIEWERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QFileInfoList>
#include <QDir>
#include <QListWidgetItem>

class FileViewerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileViewerDialog(QWidget *parent = 0);
    ~FileViewerDialog();

public:
    QLineEdit *currDir;
    QListWidget *fileListWidget;

public:
    void ShowFileInfoList(QFileInfoList list);

public slots:
    void ShowDir(QListWidgetItem *item);
    void ShowFiles(QDir dir);
    void ShowFiles();
};

#endif // FILEVIEWERDIALOG_H
