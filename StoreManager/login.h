#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "buyerdialog.h"
#include "salesdialog.h"
#include "auditordialog.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QString UID, QWidget *parent = nullptr);
    ~Login();

signals:
    void userLogout();

private slots:
    void onUserLogin();

    
    void on_pbn_buyer_clicked();

    void on_pbn_sales_clicked();

    void on_pbn_auditor_clicked();

    void on_pbn_logout_clicked();

private:
    Ui::Login* ui;
    BuyerDialog* buyerDialog;
    SalesDialog* salesDialog;
    AuditorDialog* auditorDialog;
    QString UID;
};

#endif // LOGIN_H
