#ifndef AUDITORBUYERTAB_H
#define AUDITORBUYERTAB_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class AuditorBuyerTab;
}

class AuditorBuyerTab : public QWidget
{
    Q_OBJECT

public:
    explicit AuditorBuyerTab(QWidget *parent = nullptr);
    ~AuditorBuyerTab();
    void initTableWidget();
    void update(QString GID, int num);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AuditorBuyerTab *ui;
    QStandardItemModel *model;
};

#endif // AUDITORBUYERTAB_H
