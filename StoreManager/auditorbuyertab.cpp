#include "auditorbuyertab.h"
#include "ui_auditorbuyertab.h"
#include "dbmodule.h"
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>

AuditorBuyerTab::AuditorBuyerTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuditorBuyerTab)
{
    ui->setupUi(this);
    initTableWidget();
}

AuditorBuyerTab::~AuditorBuyerTab()
{
    delete ui;
}

void AuditorBuyerTab::initTableWidget()
{
    DBmodule *dbmodule = DBmodule::getDBmodule();
    dbmodule->connect();
    model = new QStandardItemModel();
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tableView->setSelectionMode( QAbstractItemView::SingleSelection);//设置选中单个
    model->setColumnCount(5);
    model->setHeaderData(0, Qt::Horizontal, "进货单号");
    model->setHeaderData(1, Qt::Horizontal, "采购货物");
    model->setHeaderData(2, Qt::Horizontal, "采购数量");
    model->setHeaderData(3, Qt::Horizontal, "采购时间");
    model->setHeaderData(4, Qt::Horizontal, "采购人");

    int tableNum = 0;
    QString INID, GNAME, INNUMBER, JHDATE, UNAME;
    QSqlQuery query, query1;
    query = dbmodule->queryDatabase("select * from T_JHXX where SFSH = 0;");
    while(query.next()){
        QString GID, UID;
        INID = query.value("INID").toString();
        GID = query.value("GID").toString();
        UID = query.value("UID").toString();
        query1 = dbmodule->queryDatabase("select GNAME from T_HWXX where GID = '"+GID+"';");
        while(query1.next()){
            GNAME = query1.value("GNAME").toString();
        }
        query1 = dbmodule->queryDatabase("select UNAME from T_RYXX where UID = '"+UID+"';");
        while(query1.next()){
            UNAME = query1.value("UNAME").toString();
        }
        INNUMBER = QString::number(query.value("INNUMBER").toInt());
        JHDATE = query.value("JHDATE").toString();
        model->setItem(tableNum, 0, new QStandardItem(INID));
        model->setItem(tableNum, 1, new QStandardItem(GNAME));
        model->setItem(tableNum, 2, new QStandardItem(INNUMBER));
        model->setItem(tableNum, 3, new QStandardItem(JHDATE));
        model->setItem(tableNum, 4, new QStandardItem(UNAME));
        tableNum++;
    }


    dbmodule->disconnect();
}

/*
 * 审核确认
 */
void AuditorBuyerTab::on_pushButton_clicked()
{
    DBmodule *dbmodule = DBmodule::getDBmodule();
    dbmodule->connect();
    int rowIndex = ui->tableView->currentIndex().row();
    QString INID = model->data(model->index(rowIndex, 0)).toString();
    QString GNAME = model->data(model->index(rowIndex, 1)).toString();
    QString INNUMBER = model->data(model->index(rowIndex, 2)).toString();
    //qDebug()<<str<<endl;
    QDateTime current_time = QDateTime::currentDateTime();
    QString SHDATE = current_time.toString("yyyyMMddhhmmss");

    QSqlQuery query;
    QString sqlsentence("update T_JHXX set SFSH = 1, SHDATE = '"+SHDATE+"' where INID = '"+INID+"';");
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
    GSTORE += INNUMBER.toInt();

    sqlsentence = "update T_HWXX set GSTORE = "+QString::number(GSTORE)+" where GNAME = '"+GNAME+"';";
    ret = query.exec(sqlsentence);
    if(ret == false){
        qDebug()<<"update2 error"<<endl;
    }

    model->removeRow(rowIndex);
    dbmodule->disconnect();
}
