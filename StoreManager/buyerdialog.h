#ifndef BUYERDIALOG_H
#define BUYERDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include "dbmodule.h"

namespace Ui {
class BuyerDialog;
}

class BuyerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyerDialog(QString UID, QWidget *parent = nullptr);
    ~BuyerDialog();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::BuyerDialog *ui;
    DBmodule* dbmodule;
    QStandardItemModel *model;
    int tableNum;
    QString UID;
};

#endif // BUYERDIALOG_H
