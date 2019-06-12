#include "salesstatedialog.h"
#include "ui_salesstatedialog.h"
#include "dbmodule.h"
#include <QSqlQuery>

SalesStateDialog::SalesStateDialog(QString UID, QWidget *parent) :
    UID(UID),
    QDialog(parent),
    ui(new Ui::SalesStateDialog)
{
    ui->setupUi(this);
    DBmodule *dbmodule = DBmodule::getDBmodule();
    dbmodule->connect();
    model = new QStandardItemModel();
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tableView->setSelectionMode( QAbstractItemView::SingleSelection);//设置选中单个
    model->setColumnCount(8);
    model->setHeaderData(0, Qt::Horizontal, "出货单号");
    model->setHeaderData(1, Qt::Horizontal, "销售货物编号");
    model->setHeaderData(2, Qt::Horizontal, "销售货物名称");
    model->setHeaderData(3, Qt::Horizontal, "销售数量");
    model->setHeaderData(4, Qt::Horizontal, "销售时间");
    model->setHeaderData(5, Qt::Horizontal, "缺货数量");
    model->setHeaderData(6, Qt::Horizontal, "销售人");
    model->setHeaderData(7, Qt::Horizontal, "订单审核记录");

    int tableNum = 0;
    int GSTORE;
    QString OUTID, GNAME, OUTNUMBER, CHDATE, QHSL, UNAME;
    QSqlQuery query, query1;

    query = dbmodule->queryDatabase("select * from T_CHXX where UID = '"+UID+"';");
    while(query.next()){
        QString GID, UID;
        OUTID = query.value("OUTID").toString();
        GID = query.value("GID").toString();
        UID = query.value("UID").toString();
        query1 = dbmodule->queryDatabase("select GSTORE from T_HWXX where GID = '"+GID+"';");
        while(query1.next()){
            GSTORE = query1.value("GSTORE").toInt();
        }
        QHSL = QString::number(query.value("OUTNUMBER").toInt()>GSTORE?(query.value("OUTNUMBER").toInt()-GSTORE):0);
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
        int SFSH = query.value("SFSH").toInt();
        QString tmp_SFSH;
        if(SFSH == 0) tmp_SFSH = "未审核";
        else if(SFSH == 1) tmp_SFSH = "审核通过";
        else if(SFSH == 2) tmp_SFSH = "审核未通过";
        model->setItem(tableNum, 0, new QStandardItem(OUTID));
        model->setItem(tableNum, 1, new QStandardItem(GID));
        model->setItem(tableNum, 2, new QStandardItem(GNAME));
        model->setItem(tableNum, 3, new QStandardItem(OUTNUMBER));
        model->setItem(tableNum, 4, new QStandardItem(CHDATE));
        model->setItem(tableNum, 5, new QStandardItem(QHSL));
        model->setItem(tableNum, 6, new QStandardItem(UNAME));
        model->setItem(tableNum, 7, new QStandardItem(tmp_SFSH));
        tableNum++;
    }


    dbmodule->disconnect();
}

SalesStateDialog::~SalesStateDialog()
{
    delete ui;
}
