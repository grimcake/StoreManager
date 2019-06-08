#include "dbmodule.h"
#include <QDebug>
#include <QSqlQuery>

DBmodule* DBmodule::dbmodule = NULL; //类的静态成员要在类外初始化

DBmodule::DBmodule()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("storemanager");
    db.setUserName("root");
    db.setPassword("");
}

void DBmodule::connect(){
    bool ret = db.open();
    if(ret){
        qDebug()<<"open db success"<<endl;
    }
    else{
        qDebug()<<"open db failed"<<endl;
    }
}

void DBmodule::disconnect(){
    db.close();
    db.removeDatabase("storemanager");
}

DBmodule *DBmodule::getDBmodule()
{
    if(DBmodule::dbmodule == NULL){
        dbmodule = new DBmodule();
    }
    return dbmodule;
}

QSqlQuery DBmodule::queryDatabase(QString s)
{
    QSqlQuery query(db);
    query.exec(s);
    return query;
}
