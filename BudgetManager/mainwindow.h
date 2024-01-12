#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <budgetmanager.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    QDialog ExpenseEntryDialog(const QVector<Category>, BudgetManager, QWidget *parent);
    ~MainWindow();
    void addBudgetCategory(const QString& categoryName, double maxAmount, double spentAmount);

private slots:
    void on_adaugaBani_clicked();

    void on_cheltuieste_clicked();

    void on_newMonth_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
