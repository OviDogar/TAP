#include "expenseentrydialog.h"
#include "ui_expenseentrydialog.h"
#include <QComboBox>
#include "budgetmanager.h"

ExpenseEntryDialog::ExpenseEntryDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExpenseEntryDialog)
{
    ui->setupUi(this);
    QStringList categoryNames = {};

    for (const auto &category : BudgetManager::getInstance().categories) {
        categoryNames.push_back(category.name);
    }
    ui->categorie->clear();
    ui->categorie->addItems(categoryNames);

}

ExpenseEntryDialog::~ExpenseEntryDialog()
{
    delete ui;
}

void ExpenseEntryDialog::on_buttonBox_accepted()
{
    BudgetManager::getInstance().recordExpense(ui->categorie->currentText(),ui->suma->text().toDouble());
}

