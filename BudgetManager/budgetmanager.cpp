// budgetmanager.cpp
#include "budgetmanager.h"
#include <QDebug>

BudgetManager::BudgetManager() : totalIncome(0.0)
{
    // Adaugam cateva categorii default
    addIncome(2500);
    addCategory("Locuinta", 1000.0);
    addCategory("Utilitati", 200.0);
    addCategory("Alimente", 300.0);
    addCategory("Rate", 100.0);
    addCategory("Urgente", 100.0);
    addCategory("Diverse", 100.0);

    // Initializam istoricul de cheltuieli
    spendingHistory.append(QVector<double>(categories.size(), 0.0));

    // pentru testare, adaugam cateva cheltuieli
    recordExpense("Rate",50);
    recordExpense("Locuinta",750);
}

void BudgetManager::setTotalIncome(double income)
{
    totalIncome = income;
}

void BudgetManager::addIncome(const double income)
{
    totalIncome += income;
}

void BudgetManager::recordExpense(const QString &categoryName, double expense)
{
    for (auto &category : categories) {
        if (category.name == categoryName) {
            category.spent += expense;

            // Actualizam istoricul de cheltuieli pentru luna curenta
            spendingHistory.back()[&category - categories.data()] = expense;

            return;
        }
    }

    // In cazul in care categoria nu este gasita
    qDebug() << "Eroare: Categoria" << categoryName << "nu exista!";
}

double BudgetManager::calculateRemainingBudget(const QString &categoryName) const
{
    for (const auto &category : categories) {
        if (category.name == categoryName) {
            return category.budget - category.spent;
        }
    }

    // In cazul in care categoria nu este gasita
    qDebug() << "Error: Category" << categoryName << "not found!";
    return 0.0;
}

double BudgetManager::calculateTotalSpent() const
{
    double totalSpent = 0.0;

    for (const auto &category : categories) {
        totalSpent += category.spent;
    }

    return totalSpent;
}

void BudgetManager::nextMonthBudget()
{
    // Calculam media cheltuita pe fiecare categorie in ultimele luni
    QVector<double> averageSpending(categories.size(), 0.0);

    for (const auto &month : spendingHistory) {
        for (int i = 0; i < categories.size(); ++i) {
            averageSpending[i] += month[i];
        }
    }

    for (int i = 0; i < categories.size(); ++i) {
        if (spendingHistory.size() > 0) {
            averageSpending[i] /= spendingHistory.size();
        }
    }

    // Setam bugetul lunii viitoare tinand cont de media cheltuielilor anterioare + 10%
    for (int i = 0; i < categories.size(); ++i) {
        categories[i].budget = averageSpending[i] * 1.1; // Crestem cu 10%
    }

    // Initializam istoricul de cheltuieli pentru luna urmatoare
    spendingHistory.append(QVector<double>(categories.size(), 0.0));
}

void BudgetManager::addCategory(const QString &name, double budget)
{
    Category category;
    category.name = name;
    category.budget = budget;
    category.spent = 0.0;

    categories.append(category);
}

const QVector<Category> &BudgetManager::getCategories() const
{
    return categories;
}
