#include "salesdialog.h"
#include "ui_salesdialog.h"

SalesDialog::SalesDialog(QString UID, QWidget *parent) :
    UID(UID),
    QDialog(parent),
    ui(new Ui::SalesDialog)
{
    ui->setupUi(this);
}

SalesDialog::~SalesDialog()
{
    delete ui;
}
