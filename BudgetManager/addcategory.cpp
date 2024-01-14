#include "addcategory.h"
#include "ui_addcategory.h"
#include "budgetmanager.h"


AddCategory::AddCategory(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddCategory)
{
    ui->setupUi(this);
}

AddCategory::~AddCategory()
{
    delete ui;
}

void AddCategory::on_buttonBox_accepted()
{
    double amount = ui->buget->text().toDouble();
    QString categorie = ui->categorie->text();

    BudgetManager::getInstance().addCategory(categorie, amount);

}

