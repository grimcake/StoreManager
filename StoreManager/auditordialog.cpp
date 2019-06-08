#include "auditordialog.h"
#include "ui_auditordialog.h"

AuditorDialog::AuditorDialog(QString UID, QWidget *parent) :
    UID(UID),
    QDialog(parent),
    ui(new Ui::AuditorDialog)
{
    ui->setupUi(this);
}

AuditorDialog::~AuditorDialog()
{
    delete ui;
}
