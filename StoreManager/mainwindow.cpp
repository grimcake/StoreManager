#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loginWidget = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete loginWidget;
}


void MainWindow::on_pushButton_clicked()
{
    if(ui->user_name->text().isEmpty()){
        QMessageBox::critical(this, "Error", "name can't be empty");
        return;
    }
    if(ui->user_pwd->text().isEmpty()){
        QMessageBox::critical(this, "Error", "pass can't be empty");
        return;
    }
    QString name = ui->user_name->text();
    QString pwd = ui->user_pwd->text();

    //check login imformation
    DBmodule* dbmodule = DBmodule::getDBmodule();
    QSqlQuery query;
    dbmodule->connect();
    query = dbmodule->queryDatabase("select UPASS from T_RYXX where UID = " + name + ";");
    while(query.next()){
        if(query.value("UPASS") == pwd){
            if(loginWidget != NULL){
                delete loginWidget;
            }
            loginWidget = new Login(name);
            QObject::connect(this, SIGNAL(userLogin()), loginWidget, SLOT(onUserLogin()));
            QObject::connect(loginWidget, SIGNAL(userLogout()), this, SLOT(onUserLogout()));
            emit userLogin();
            this->hide();
        }
        else{
            QMessageBox::critical(this, "ERROR", "ID or pass not correct");
        }
    }
    dbmodule->disconnect();

}

void MainWindow::onUserLogout()
{
    loginWidget->hide();
    this->show();

}
