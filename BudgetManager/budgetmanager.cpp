// budgetmanager.cpp
#include "budgetmanager.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/qsqlquery.h>
#include <QSqlError>

BudgetManager::BudgetManager() : totalIncome(0.0)
{
    // Incarcam datele din sql
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mydatabase.db");

    if (db.open()) {
        QSqlQuery query("SELECT maxAmount FROM budget");
        if (query.next()) {
            double loadedMaxAmount = query.value(0).toDouble();
            addIncome(loadedMaxAmount);
        }

        QSqlQuery query1("SELECT name,budget,spent FROM categories");

        // Daca interogarea a fost reusita
        if (query1.exec()) {
            // trecem prin tot set-ul de date
            while (query1.next()) {
                addCategory(query1.value("name").toString(), query1.value("budget").toDouble(), query1.value("spent").toDouble());
            }
        } else {
            qDebug() << "Nu s-a rulat interogarea DB:" << query1.lastError().text();
        }

        db.close();
    }

    // Initializam istoricul de cheltuieli
    spendingHistory.append(QVector<double>(categories.size(), 0.0));
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
    qDebug() << "Error: Categoria" << categoryName << "nu exista!";
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


void BudgetManager::addCategory(const QString &name, double budget, double spent)
{
    Category category;
    category.name = name;
    category.budget = budget;
    category.spent = spent;

    categories.append(category);
}

const QVector<Category> &BudgetManager::getCategories() const
{
    return categories;
}
