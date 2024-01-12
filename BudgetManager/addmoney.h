#ifndef ADDMONEY_H
#define ADDMONEY_H

#include <QDialog>

namespace Ui {
class AddMoney;
}

class AddMoney : public QDialog
{
    Q_OBJECT

public:
    explicit AddMoney(QWidget *parent = nullptr);
    ~AddMoney();

private slots:
    void on_buttonBox_accepted();

signals:
    void amountUpdated(double amount);

private:
    Ui::AddMoney *ui;
};

#endif // ADDMONEY_H
