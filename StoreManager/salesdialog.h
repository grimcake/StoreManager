#ifndef SALESDIALOG_H
#define SALESDIALOG_H

#include <QDialog>

namespace Ui {
class SalesDialog;
}

class SalesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SalesDialog(QString UID, QWidget *parent = nullptr);
    ~SalesDialog();

private:
    Ui::SalesDialog *ui;
    QString UID;
};

#endif // SALESDIALOG_H
