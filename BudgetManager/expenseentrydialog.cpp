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

    for (const auto &category : BudgetManager().categories) {
        categoryNames.push_back(category.name);
    }
    ui->categorie->clear();
    ui->categorie->addItems(categoryNames);

    //connect(ui->categorie, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &YourClassName::categoryChanged);


}

ExpenseEntryDialog::~ExpenseEntryDialog()
{
    delete ui;
}

void ExpenseEntryDialog::on_buttonBox_accepted()
{
    BudgetManager().recordExpense(ui->categorie->currentText(),ui->suma->text().toDouble());
}

