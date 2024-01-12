#include "expenseentrydialog.h"
#include "ui_expenseentrydialog.h"

ExpenseEntryDialog::ExpenseEntryDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExpenseEntryDialog)
{
    ui->setupUi(this);
}

ExpenseEntryDialog::~ExpenseEntryDialog()
{
    delete ui;
}
