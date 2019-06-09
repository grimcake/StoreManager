#include "auditorsalestab.h"
#include "ui_auditorsalestab.h"
#include "dbmodule.h"
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>

AuditorSalesTab::AuditorSalesTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuditorSalesTab)
{
    ui->setupUi(this);
    initTableWidget();
}

AuditorSalesTab::~AuditorSalesTab()
{
    delete ui;
}

void AuditorSalesTab::initTableWidget()
{
    DBmodule *dbmodule = DBmodule::getDBmodule();
    dbmodule->connect();
    model = new QStandardItemModel();
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tableView->setSelectionMode( QAbstractItemView::SingleSelection);//设置选中单个
    model->setColumnCount(6);
    model->setHeaderData(0, Qt::Horizontal, "出货单号");
    model->setHeaderData(1, Qt::Horizontal, "销售货物");
    model->setHeaderData(2, Qt::Horizontal, "销售数量");
    model->setHeaderData(3, Qt::Horizontal, "销售时间");
    model->setHeaderData(4, Qt::Horizontal, "缺货数量");
    model->setHeaderData(5, Qt::Horizontal, "销售人");

    int tableNum = 0;
    QString OUTID, GNAME, OUTNUMBER, CHDATE, QHSL, UNAME;
    QSqlQuery query, query1;
    query = dbmodule->queryDatabase("select * from T_CHXX where SFSH = 0;");
    while(query.next()){
        QString GID, UID;
        OUTID = query.value("OUTID").toString();
        GID = query.value("GID").toString();
        UID = query.value("UID").toString();
        QHSL = query.value("QHSL").toString();
        query1 = dbmodule->queryDatabase("select GNAME from T_HWXX where GID = '"+GID+"';");
        while(query1.next()){
            GNAME = query1.value("GNAME").toString();
        }
        query1 = dbmodule->queryDatabase("select UNAME from T_RYXX where UID = '"+UID+"';");
        while(query1.next()){
            UNAME = query1.value("UNAME").toString();
        }
        OUTNUMBER = QString::number(query.value("OUTNUMBER").toInt());
        CHDATE = query.value("CHDATE").toString();
        model->setItem(tableNum, 0, new QStandardItem(OUTID));
        model->setItem(tableNum, 1, new QStandardItem(GNAME));
        model->setItem(tableNum, 2, new QStandardItem(OUTNUMBER));
        model->setItem(tableNum, 3, new QStandardItem(CHDATE));
        model->setItem(tableNum, 4, new QStandardItem(QHSL));
        model->setItem(tableNum, 5, new QStandardItem(UNAME));
        tableNum++;
    }


    dbmodule->disconnect();
}

void AuditorSalesTab::on_pushButton_clicked()
{
    DBmodule *dbmodule = DBmodule::getDBmodule();
    dbmodule->connect();
    int rowIndex = ui->tableView->currentIndex().row();
    QString OUTID = model->data(model->index(rowIndex, 0)).toString();
    QString GNAME = model->data(model->index(rowIndex, 1)).toString();
    QString OUTNUMBER = model->data(model->index(rowIndex, 2)).toString();
    QString QHSL = model->data(model->index(rowIndex, 4)).toString();
    //qDebug()<<str<<endl;
    QDateTime current_time = QDateTime::currentDateTime();
    QString SHDATE = current_time.toString("yyyyMMddhhmmss");

    QSqlQuery query;
    QString sqlsentence("update T_CHXX set SFSH = 1, SHDATE = '"+SHDATE+"' where OUTID = '"+OUTID+"';");
    qDebug()<<sqlsentence<<endl;
    bool ret = query.exec(sqlsentence);
    if(ret == false){
        qDebug()<<"update error"<<endl;
    }

    int GSTORE = 0;
    query = dbmodule->queryDatabase("select GSTORE from T_HWXX where GNAME = '"+GNAME+"';");
    while(query.next()){
        GSTORE = query.value("GSTORE").toInt();
    }
    GSTORE -= OUTNUMBER.toInt();

    if(QHSL.toInt() == 0){
        sqlsentence = "update T_HWXX set GSTORE = "+QString::number(GSTORE)+" where GNAME = '"+GNAME+"';";
        ret = query.exec(sqlsentence);
        if(ret == false){
            qDebug()<<"update2 error"<<endl;
        }


    }
    model->removeRow(rowIndex);
    dbmodule->disconnect();
}
