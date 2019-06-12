#include "buyerdialog.h"
#include "ui_buyerdialog.h"
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>
#include <QTableWidgetItem>

BuyerDialog::BuyerDialog(QString UID, QWidget *parent) :
    UID(UID),
    QDialog(parent),
    ui(new Ui::BuyerDialog)
{
    ui->setupUi(this);
    DBmodule* dbmodule = DBmodule::getDBmodule();
    dbmodule->connect();
    QSqlQuery query;
    query = dbmodule->queryDatabase("select GNAME from T_HWXX;");
    while(query.next()){
        //qDebug()<<query.value("GNAME").toString()<<endl;
        ui->comboBox->addItem(query.value("GNAME").toString());
    }
    dbmodule->disconnect();

    model = new QStandardItemModel();
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tableView->setSelectionMode( QAbstractItemView::SingleSelection);//设置选中单个
    model->setColumnCount(3);
    model->setHeaderData(0, Qt::Horizontal, "采购货物");
    model->setHeaderData(1, Qt::Horizontal, "采购数量");
    model->setHeaderData(2, Qt::Horizontal, "采购时间");
    tableNum = 0;
}

BuyerDialog::~BuyerDialog()
{
    delete ui;
    delete dbmodule;
}

void BuyerDialog::on_pushButton_clicked()
{
    QString name = ui->comboBox->currentText();
    QString num = ui->lineEdit->text();
    QDateTime current_time = QDateTime::currentDateTime();
    QString time = current_time.toString("yyyy.MM.dd hh:mm ddd");
    model->setItem(tableNum, 0, new QStandardItem(name));
    model->setItem(tableNum, 1, new QStandardItem(num));
    model->setItem(tableNum, 2, new QStandardItem(time));

    tableNum++;
    ui->lineEdit->text() = "";
}

void BuyerDialog::on_pushButton_4_clicked()
{
    int rowIndex = ui->tableView->currentIndex().row();
    model->removeRow(rowIndex);
    tableNum--;
}

void BuyerDialog::on_pushButton_5_clicked()
{
    model->removeRows(0, model->rowCount());
    tableNum = 0;
}

void BuyerDialog::on_pushButton_3_clicked()
{
    int rowIndex = ui->tableView->currentIndex().row();
    QString INID, GID, UID, JHDATE, SHDATE("NULL");
    int INNUMBER, SFSH;

    DBmodule* dbmodule = DBmodule::getDBmodule();
    dbmodule->connect();
    QSqlQuery query;

    //生成最大的单号
    query = dbmodule->queryDatabase("select max(INID) from T_JHXX;");
    while(query.next()){
        //QString补足6位前导0的方法
        INID = QString("%1").arg(query.value("max(INID)").toString().toInt()+1, 6, 10, QChar('0'));
    }


    query = dbmodule->queryDatabase("select GID from T_HWXX where GNAME = '"+model->data(model->index(rowIndex, 0)).toString()+"';");
    while(query.next()){
        GID = query.value("GID").toString();
    }


    UID = this->UID;


    QDateTime current_time = QDateTime::currentDateTime();
    JHDATE = current_time.toString("yyyyMMdd");


    INNUMBER = model->data(model->index(rowIndex, 1)).toInt();
    SFSH = 0;

    //qDebug()<<INID<<" "<<GID<<" "<<INNUMBER<<" "<<UID<<" "<<SHDATE<<" "<<SFSH<<" "<<JHDATE<<endl;
    QString sqlsentence("insert into T_JHXX values('"+INID+"','"+GID+"',"+QString::number(INNUMBER)+",'"+UID+"',"+SHDATE+","+QString::number(SFSH)+","+JHDATE+");");
    qDebug()<<sqlsentence<<endl;
    bool ret = query.exec(sqlsentence);
    if(ret == false){
        qDebug()<<"insert error"<<endl;
    }
    model->removeRow(rowIndex);
    dbmodule->disconnect();

}

