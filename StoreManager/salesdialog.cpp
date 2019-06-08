#include "salesdialog.h"
#include "ui_salesdialog.h"
#include "dbmodule.h"
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>
#include <QTableWidgetItem>

SalesDialog::SalesDialog(QString UID, QWidget *parent) :
    UID(UID),
    QDialog(parent),
    ui(new Ui::SalesDialog)
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

SalesDialog::~SalesDialog()
{
    delete ui;
    delete dbmodule;
}

void SalesDialog::on_pushButton_clicked()
{
    QString name = ui->comboBox->currentText();
    QString num = ui->lineEdit->text();
    QDateTime current_time = QDateTime::currentDateTime();
    QString time = current_time.toString("yyyy.MM.dd hh:mm ddd");
    model->setItem(tableNum, 0, new QStandardItem(name));
    model->setItem(tableNum, 1, new QStandardItem(num));
    model->setItem(tableNum, 2, new QStandardItem(time));
    tableNum++;
}

void SalesDialog::on_pushButton_4_clicked()
{
    int rowIndex = ui->tableView->currentIndex().row();
    model->removeRow(rowIndex);
    tableNum--;
}

void SalesDialog::on_pushButton_5_clicked()
{
    model->removeRows(0, model->rowCount());
    tableNum = 0;
}

void SalesDialog::on_pushButton_3_clicked()
{
    QString OUTID, GID, UID, CHDATE, SHDATE("NULL");
    int OUTNUMBER, SFSH, QHSL, YYSL=0;

    DBmodule* dbmodule = DBmodule::getDBmodule();
    dbmodule->connect();
    QSqlQuery query;

    //生成最大的单号
    query = dbmodule->queryDatabase("select max(OUTID) from T_CHXX;");
    while(query.next()){
        //QString补足6位前导0的方法
        OUTID = QString("%1").arg(query.value("max(OUTID)").toString().toInt()+1, 6, 10, QChar('0'));
    }


    query = dbmodule->queryDatabase("select GID from T_HWXX where GNAME = '"+ui->comboBox->currentText()+"';");
    while(query.next()){
        GID = query.value("GID").toString();
    }


    UID = this->UID;


    QDateTime current_time = QDateTime::currentDateTime();
    CHDATE = current_time.toString("yyyyMMdd");


    OUTNUMBER = ui->lineEdit->text().toInt();
    SFSH = 0;

    //查询原有货物数量
    query = dbmodule->queryDatabase("select GSTORE from T_HWXX where GID='"+GID+"';");
    while(query.next()){
        YYSL = query.value("GSTORE").toInt();
    }
    QHSL = (YYSL>OUTNUMBER)?0:(OUTNUMBER-YYSL);

    //qDebug()<<INID<<" "<<GID<<" "<<INNUMBER<<" "<<UID<<" "<<SHDATE<<" "<<SFSH<<" "<<JHDATE<<endl;
    QString sqlsentence("insert into T_CHXX values('"+OUTID+"','"+GID+"',"+QString::number(OUTNUMBER)+",'"+UID+"',"+SHDATE+","+QString::number(SFSH)+","+QString::number(QHSL)+","+CHDATE+");");
    qDebug()<<sqlsentence<<endl;
    bool ret = query.exec(sqlsentence);
    if(ret == false){
        qDebug()<<"insert error"<<endl;
    }

    dbmodule->disconnect();
}
