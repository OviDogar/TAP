// budgetmanager.h
#ifndef BUDGETMANAGER_H
#define BUDGETMANAGER_H

#define DEFAULT_BUDGET 5000

#include <QString>
#include <QVector>

class Category {
public:
    QString name;
    double budget;
    double spent;
};

class BudgetManager {
public:
    double totalIncome;
    QVector<Category> categories;
    QVector<QVector<double>> spendingHistory; // istoricul cheltuielilor

public:
    static BudgetManager& getInstance() {
        static BudgetManager instance;  // Static instance created once
        return instance;
    }

    void setTotalIncome(double income);
    void addCategory(const QString &name, double budget, double spent=0.0);
    void addIncome(const double income);
    void recordExpense(const QString &categoryName, double expense);
    void recordIncome(double income);
    double calculateRemainingBudget(const QString &categoryName) const;
    double calculateTotalSpent() const;
    void nextMonthBudget();
    const QVector<Category> &getCategories() const;

private:
    BudgetManager(); // Private constructor to enforce singleton
    ~BudgetManager() = default;
    BudgetManager(const BudgetManager&) = delete;
    BudgetManager& operator=(const BudgetManager&) = delete;
};

#endif // BUDGETMANAGER_H
