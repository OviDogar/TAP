// mainwindow.cpp
#include "mainwindow.h"

ExpenseEntryDialog::ExpenseEntryDialog(const QVector<Category> &categories, BudgetManager &bm, QWidget *parent)
    : QDialog(parent), budgetManager(bm)
{
    setWindowTitle("Enter Expenses");

    mainLayout = new QVBoxLayout();

    categoryComboBox = new QComboBox(this);
    for (const auto &category : categories) {
        categoryComboBox->addItem(category.name);
    }

    expenseLineEdit = new QLineEdit(this);
    expenseLineEdit->setValidator(new QDoubleValidator(0.0, 1000000.0, 2, expenseLineEdit));

    descriptionLineEdit = new QLineEdit(this);

    okButton = new QPushButton("OK", this);
    connect(okButton, &QPushButton::clicked, this, &ExpenseEntryDialog::handleExpenseEntry);

    mainLayout->addWidget(new QLabel("Description:", this));
    mainLayout->addWidget(descriptionLineEdit);
    mainLayout->addWidget(new QLabel("Category:", this));
    mainLayout->addWidget(categoryComboBox);
    mainLayout->addWidget(new QLabel("Expense:", this));
    mainLayout->addWidget(expenseLineEdit);
    mainLayout->addWidget(okButton);

    setLayout(mainLayout);
}

void ExpenseEntryDialog::handleExpenseEntry()
{
    QString categoryName = categoryComboBox->currentText();
    double expense = expenseLineEdit->text().toDouble();

    if (expense < 0) {
        QMessageBox::warning(this, "Invalid Expense", "Expense cannot be negative.");
        return;
    }

    budgetManager.recordExpense(categoryName, expense);

    accept();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), expenseEntryDialog(nullptr)
{
    setWindowTitle("Friendly Budget");

    mainLayout = new QVBoxLayout();

    totalIncomeLineEdit = new QLineEdit(this);
    totalIncomeLineEdit->setPlaceholderText("Enter total income");

    calculateButton = new QPushButton("Calculate Budget", this);
    connect(calculateButton, &QPushButton::clicked, this, &MainWindow::handleBudgetCalculation);

    expenseEntryButton = new QPushButton("Enter Expenses", this);
    connect(expenseEntryButton, &QPushButton::clicked, this, &MainWindow::handleExpenseEntry);

    nextMonthButton = new QPushButton("Next Month Budget", this); // Added button for next month budget
    connect(nextMonthButton, &QPushButton::clicked, this, &MainWindow::handleNextMonthBudget);

    statusLabel = new QLabel(this);

    mainLayout->addWidget(totalIncomeLineEdit);
    mainLayout->addWidget(calculateButton);
    mainLayout->addWidget(expenseEntryButton);
    mainLayout->addWidget(nextMonthButton);
    mainLayout->addWidget(statusLabel);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::handleBudgetCalculation()
{
    bool ok;
    double totalIncome = totalIncomeLineEdit->text().toDouble(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid total income.");
        return;
    }

    budgetManager.setTotalIncome(totalIncome);

    // Show UI for expense entry
    handleExpenseEntry();

    // Example of how to display budget information
    QString budgetInfo = "Budget Information:\n";
    for (const auto &category : budgetManager.getCategories()) {
        budgetInfo += QString("%1: %2\n").arg(category.name).arg(category.budget);
    }

    statusLabel->setText(budgetInfo);
}

void MainWindow::handleExpenseEntry()
{
    if (!expenseEntryDialog) {
        expenseEntryDialog = new ExpenseEntryDialog(budgetManager.getCategories(), budgetManager, this);
    }

    expenseEntryDialog->exec();
}

void MainWindow::handleNextMonthBudget()
{
    budgetManager.nextMonthBudget();

    // Example of how to display updated budget information
    QString budgetInfo = "Budget Information:\n";
    for (const auto &category : budgetManager.getCategories()) {
        budgetInfo += QString("%1: %2\n").arg(category.name).arg(category.budget);
    }

    statusLabel->setText(budgetInfo);
}

MainWindow::~MainWindow()
{
    if (expenseEntryDialog) {
        delete expenseEntryDialog;
    }
}
