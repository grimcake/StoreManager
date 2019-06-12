#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QSqlQuery>

Login::Login(QString UID, QWidget *parent) :
    UID(UID),
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    buyerDialog = new BuyerDialog(UID);
    salesDialog = new SalesDialog(UID);
    auditorDialog = new AuditorDialog(UID);
    buyercalldialog = new BuyerCallDialog();

    buyerstatedialog = NULL;
    salesstatedialog = NULL;
    //buyerstatedialog = new BuyerStateDialog(UID);
    //salesstatedialog = new SalesStateDialog(UID);

    //查询人员身份，显示不同的窗口
    QSqlQuery query;
    dbmodule = DBmodule::getDBmodule();
    dbmodule->connect();
    query = dbmodule->queryDatabase("select UJOB from T_RYXX where UID = '"+UID+"';");
    while(query.next()){
        int UJOB = query.value("UJOB").toInt();
        if(UJOB == 1){
            ui->pbn_auditor->hide();
            ui->pbn_sales->hide();
            ui->pushButton_3->hide();
            ui->pushButton_4->hide();
        }
        else if(UJOB == 2){
            ui->pbn_buyer->hide();
            ui->pbn_auditor->hide();
            ui->pushButton->hide();
            ui->pushButton_2->hide();
            ui->pushButton_4->hide();
        }
        else if(UJOB == 3){
            ui->pbn_buyer->hide();
            ui->pbn_sales->hide();
            ui->pushButton->hide();
            ui->pushButton_2->hide();
            ui->pushButton_3->hide();
            ui->pushButton_4->hide();
        }

    }

    dbmodule->disconnect();
}

Login::~Login()
{
    delete ui;
    /*delete buyerDialog;
    delete salesDialog;
    delete auditorDialog;*/
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
    if(salesDialog!=NULL) salesDialog->hide();
    if(buyerDialog!=NULL) buyerDialog->hide();
    if(buyerstatedialog!=NULL) buyerstatedialog->hide();
    if(salesstatedialog!=NULL) salesstatedialog->hide();
    if(buyercalldialog!=NULL) buyercalldialog->hide();
    if(auditorDialog!=NULL) auditorDialog->hide();
    emit userLogout();
}

void Login::on_pushButton_clicked()
{
    buyercalldialog->show();
}

/*
 * 进货订单审核状态
 */
void Login::on_pushButton_2_clicked()
{
    buyerstatedialog = new BuyerStateDialog(UID);
    buyerstatedialog->show();
}


/*
 * 出货订单审核状态
 */
void Login::on_pushButton_3_clicked()
{
    salesstatedialog = new SalesStateDialog(UID);
    salesstatedialog->show();
}

/*
 * 订单审核记录
 */
void Login::on_pushButton_4_clicked()
{

}
