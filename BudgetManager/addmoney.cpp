#include "addmoney.h"
#include "ui_addmoney.h"
#include "budgetmanager.h"
#include "QString"

AddMoney::AddMoney(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddMoney)
{
    ui->setupUi(this);
}

AddMoney::~AddMoney()
{
    delete ui;
}

void AddMoney::on_buttonBox_accepted()
{
    double amount = ui->addAmount->text().toDouble();
    BudgetManager::getInstance().addIncome(amount);

    emit amountUpdated(amount);

}


