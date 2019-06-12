#ifndef STATEDIALOG_H
#define STATEDIALOG_H

#include <QDialog>

namespace Ui {
class StateDialog;
}

class StateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StateDialog(QWidget *parent = nullptr);
    ~StateDialog();

private:
    Ui::StateDialog *ui;
};

#endif // STATEDIALOG_H
