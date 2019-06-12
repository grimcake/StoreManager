#ifndef SALESSTATEDIALOG_H
#define SALESSTATEDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class SalesStateDialog;
}

class SalesStateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SalesStateDialog(QString UID, QWidget *parent = nullptr);
    ~SalesStateDialog();

private:
    Ui::SalesStateDialog *ui;
    QStandardItemModel *model;
    QString UID;
};

#endif // SALESSTATEDIALOG_H
