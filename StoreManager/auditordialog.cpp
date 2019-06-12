#include "auditordialog.h"
#include "ui_auditordialog.h"

AuditorDialog::AuditorDialog(QString UID, QWidget *parent) :
    UID(UID),
    QDialog(parent),
    ui(new Ui::AuditorDialog)
{
    ui->setupUi(this);
    buyertab = new AuditorBuyerTab();
    salestab = new AuditorSalesTab();
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->insertTab(0, buyertab, tr("进货单审核"));
    ui->tabWidget->insertTab(1, salestab, tr("出货单审核"));
    ui->tabWidget->removeTab(2);

}

AuditorDialog::~AuditorDialog()
{
    delete ui;
}

void AuditorDialog::on_pushButton_clicked()
{

}


