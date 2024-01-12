#ifndef EXPENSEENTRYDIALOG_H
#define EXPENSEENTRYDIALOG_H

#include <QDialog>

namespace Ui {
class ExpenseEntryDialog;
}

class ExpenseEntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExpenseEntryDialog(QWidget *parent = 0);
    ~ExpenseEntryDialog();

private:
    Ui::ExpenseEntryDialog *ui;
};

#endif // EXPENSEENTRYDIALOG_H
