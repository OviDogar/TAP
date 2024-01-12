#include "mainwindow.h"
#include "expenseentrydialog.h"
#include "addmoney.h"
#include "ui_mainwindow.h"
#include "budgetmanager.h"
#include <QtGui>
#include <QtGui>
#include <ctime>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/qsqlquery.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Get the current time
    std::time_t currentTime = std::time(nullptr);
    std::tm *localTime = std::localtime(&currentTime);

    // Array of month names in Romanian
    const char* monthNames[] = {
        "Ianuarie", "Februarie", "Martie", "Aprilie", "Mai", "Iunie",
        "Iulie", "August", "Septembrie", "Octombrie", "Noiembrie", "Decembrie"
    };


    ui->monthYear->setText(QString("%1 %2").arg(monthNames[localTime->tm_mon]).arg(localTime->tm_year + 1900));
    ui->labBuget->setText(QString("Buget: %1RON").arg(BudgetManager().totalIncome));
    ui->labCheltuit->setText(QString("Cheltuit: %1RON").arg(BudgetManager().calculateTotalSpent()));
    ui->labRamas->setText(QString("Ramas: %1RON").arg(BudgetManager().totalIncome - BudgetManager().calculateTotalSpent()));

    for (const auto &category : BudgetManager().categories) {
        this->addBudgetCategory(category.name, category.budget, category.spent);

    }

}

MainWindow::~MainWindow()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mydatabase.db");

    if (db.open()) {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS budget (settings INT PRIMARY KEY, maxAmount REAL, spentAmount REAL)");

        query.prepare("INSERT OR REPLACE INTO budget (settings, maxAmount, spentAmount) VALUES (:settings, :maxAmount, :spentAmount)");
        query.bindValue(":settings", 1);
        query.bindValue(":maxAmount", BudgetManager().totalIncome);
        query.bindValue(":spentAmount", BudgetManager().calculateTotalSpent());
        query.exec();

        query.exec("CREATE TABLE IF NOT EXISTS categories (name TEXT PRIMARY KEY, budget REAL, spent REAL)");

        for (const auto &category : BudgetManager().categories) {
            query.prepare("INSERT OR REPLACE INTO categories (name, budget, spent) VALUES (:name, :budget, :spent)");
            query.bindValue(":name", category.name);
            query.bindValue(":budget", category.budget);
            query.bindValue(":spent", category.spent);
            query.exec();
        }

        db.close();
    }

    delete ui;
}


void MainWindow::on_adaugaBani_clicked()
{
    class AddMoney *addMoney = new class AddMoney(this);
    addMoney->exec();

}

void MainWindow::on_cheltuieste_clicked()
{
    class ExpenseEntryDialog *addExpense = new class ExpenseEntryDialog(this);
    addExpense->exec();
}



void MainWindow::on_newMonth_clicked()
{

}


void MainWindow::addBudgetCategory(const QString& categoryName, double maxAmount, double spentAmount) {
    QLabel* nameLabel = new QLabel(categoryName, ui->centralwidget);
    QProgressBar* progressBar = new QProgressBar(ui->centralwidget);
    QPushButton* addButton = new QPushButton("Adauga", ui->centralwidget);

    // Setam valoarea maxima pentru progress bar
    progressBar->setMaximum(static_cast<int>(maxAmount));

    // Setam valoarea curenta pentru progress bar
    progressBar->setValue(static_cast<int>(spentAmount));
    QString text = QString(" %v RON (%p%)");
    progressBar->setFormat(text);
    progressBar->setAlignment(Qt::AlignCenter);

    // Connectam semnalul de clicked la un slot (e.g., addExpenseClicked)
//    connect(addButton, &QPushButton::clicked, this, &AddMoney::addExpenseClicked);

    // Addaugam controalele la layout
    ui->gridLayout->addWidget(nameLabel);
    ui->gridLayout->addWidget(progressBar);
    ui->gridLayout->addWidget(addButton);

}
