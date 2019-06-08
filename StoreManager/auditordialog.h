#ifndef AUDITORDIALOG_H
#define AUDITORDIALOG_H

#include <QDialog>

namespace Ui {
class AuditorDialog;
}

class AuditorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuditorDialog(QString UID, QWidget *parent = nullptr);
    ~AuditorDialog();

private:
    Ui::AuditorDialog *ui;
    QString UID;
};

#endif // AUDITORDIALOG_H
