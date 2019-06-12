#ifndef BUYERSTATEDIALOG_H
#define BUYERSTATEDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class BuyerStateDialog;
}

class BuyerStateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyerStateDialog(QString UID, QWidget *parent = nullptr);
    ~BuyerStateDialog();

private:
    Ui::BuyerStateDialog *ui;
    QStandardItemModel *model;
    QString UID;
};

#endif // BUYERSTATEDIALOG_H
