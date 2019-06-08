#ifndef DBMODULE_H
#define DBMODULE_H
#include <QSqlDatabase>
#include <QString>

class DBmodule
{
public:
    DBmodule();
    void connect();
    void disconnect();
    QSqlQuery queryDatabase(QString s);
    static DBmodule* getDBmodule();
private:
    /* 与数据库只能连接一次，如果创建多个对象连接，会无法open，应该创建一个静态的DBmodule对象，
     * 用于所有模块与数据库连接*/
    static DBmodule *dbmodule;
    QSqlDatabase db;
};

#endif // DBMODULE_H
