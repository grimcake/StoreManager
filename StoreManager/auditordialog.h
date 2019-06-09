#ifndef AUDITORDIALOG_H
#define AUDITORDIALOG_H

#include <QDialog>
#include "auditorbuyertab.h"
#include "auditorsalestab.h"

namespace Ui {
class AuditorDialog;
}

class AuditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuditorDialog(QString UID, QWidget *parent = nullptr);
    ~AuditorDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AuditorDialog *ui;
    QString UID;
    AuditorBuyerTab *buyertab;
    AuditorSalesTab *salestab;
};

#endif // AUDITORDIALOG_H
