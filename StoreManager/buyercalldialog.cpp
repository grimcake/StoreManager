#include "buyercalldialog.h"
#include "ui_buyercalldialog.h"
#include "dbmodule.h"
#include <QSqlQuery>

BuyerCallDialog::BuyerCallDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyerCallDialog)
{
    ui->setupUi(this);
    DBmodule *dbmodule = DBmodule::getDBmodule();
    dbmodule->connect();
    model = new QStandardItemModel();
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tableView->setSelectionMode( QAbstractItemView::SingleSelection);//设置选中单个
    model->setColumnCount(2);
    model->setHeaderData(0, Qt::Horizontal, "货品编号");
    model->setHeaderData(1, Qt::Horizontal, "缺货数量");

    int tableNum = 0;
    QString INID, GNAME, INNUMBER, JHDATE, UNAME;
    QSqlQuery query;
    query = dbmodule->queryDatabase("select * from T_CHXX where QHSL>0;");
    while(query.next()){
        QString GID, QHSL;
        GID = query.value("GID").toString();
        QHSL = query.value("QHSL").toString();
        model->setItem(tableNum, 0, new QStandardItem(GID));
        model->setItem(tableNum, 1, new QStandardItem(QHSL));
        tableNum++;
    }


    dbmodule->disconnect();
}

BuyerCallDialog::~BuyerCallDialog()
{
    delete ui;
}
