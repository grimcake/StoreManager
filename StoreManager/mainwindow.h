#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "dbmodule.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void onUserLogout();

signals:
    void userLogin();

private:
    Ui::MainWindow *ui;
    Login* loginWidget;
    DBmodule *dbmodule;
};

#endif // MAINWINDOW_H
