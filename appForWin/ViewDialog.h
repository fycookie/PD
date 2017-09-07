#ifndef VIEWDIALOG_H
#define VIEWDIALOG_H

#include <QDialog>

namespace Ui{
class ViewDialog;
}

class ViewDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ViewDialog(QWidget *parent = 0);
    ~ViewDialog() {}

signals:

public slots:

private:
    Ui::ViewDialog *ui;
};

#endif // VIEWDIALOG_H
