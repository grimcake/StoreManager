#ifndef SALESDIALOG_H
#define SALESDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include "dbmodule.h"
namespace Ui {
class SalesDialog;
}

class SalesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SalesDialog(QString UID, QWidget *parent = nullptr);
    ~SalesDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::SalesDialog *ui;
    DBmodule* dbmodule;
    QStandardItemModel *model;
    int tableNum;
    QString UID;
};

#endif // SALESDIALOG_H
