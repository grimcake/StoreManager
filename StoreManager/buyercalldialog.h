#ifndef BUYERCALLDIALOG_H
#define BUYERCALLDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class BuyerCallDialog;
}

class BuyerCallDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyerCallDialog(QWidget *parent = nullptr);
    ~BuyerCallDialog();

private:
    Ui::BuyerCallDialog *ui;
    QStandardItemModel *model;
};

#endif // BUYERCALLDIALOG_H
