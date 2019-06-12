#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "buyerdialog.h"
#include "salesdialog.h"
#include "auditordialog.h"
#include "buyercalldialog.h"
#include "dbmodule.h"
#include "buyerstatedialog.h"
#include "salesstatedialog.h"

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

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Login* ui;
    BuyerDialog* buyerDialog;
    SalesDialog* salesDialog;
    AuditorDialog* auditorDialog;
    BuyerCallDialog* buyercalldialog;
    QString UID;
    DBmodule *dbmodule;

    BuyerStateDialog *buyerstatedialog;
    SalesStateDialog *salesstatedialog;

};

#endif // LOGIN_H
