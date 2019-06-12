#ifndef AUDITORSALESTAB_H
#define AUDITORSALESTAB_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class AuditorSalesTab;
}

class AuditorSalesTab : public QWidget
{
    Q_OBJECT

public:
    explicit AuditorSalesTab(QWidget *parent = nullptr);
    ~AuditorSalesTab();
    void initTableWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AuditorSalesTab *ui;
    QStandardItemModel *model;
};

#endif // AUDITORSALESTAB_H
