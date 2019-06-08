#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"

Login::Login(QString UID, QWidget *parent) :
    UID(UID),
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    buyerDialog = new BuyerDialog(UID);
    salesDialog = new SalesDialog(UID);
    auditorDialog = new AuditorDialog(UID);
}

Login::~Login()
{
    delete ui;
    delete buyerDialog;
    delete salesDialog;
    delete auditorDialog;
}


void Login::onUserLogin()
{
    this->show();
}

void Login::on_pbn_buyer_clicked()
{
    buyerDialog->show();
}

void Login::on_pbn_sales_clicked()
{
    salesDialog->show();
}

void Login::on_pbn_auditor_clicked()
{
    auditorDialog->show();
}

void Login::on_pbn_logout_clicked()
{
    emit userLogout();
}
