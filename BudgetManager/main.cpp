#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BudgetManager& budget = BudgetManager::getInstance();
    MainWindow w;
    w.show();
    return a.exec();
}
