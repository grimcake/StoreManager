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
}

MainWindow::~MainWindow()
{
    delete ui;
    delete loginWidget;
}


void test(){

}
template<class T, class...Args>
QString test(T first, Args... args){
    static QString res;
    qDebug()<<typeid(T).name()<<" "<<first<<endl;
    if(typeid (T).name() == "i"){

    }
    //else res = res+first+" ";
    test(args...);
    return res;
}


void MainWindow::on_pushButton_clicked()
{
    QString rres;
    //rres = test<int, int, QString>(2, 3, "wd");
    rres += QString(3);
    std::cout<<rres<<endl;
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
