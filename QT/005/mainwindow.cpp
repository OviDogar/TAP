#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mydialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->plainTextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionModal_triggered()
{
    MyDialog modalDialog;
    modalDialog.setModal(true);
    modalDialog.exec();
}

void MainWindow::on_actionModeless_triggered()
{
    mDialog=new MyDialog(this);
    mDialog->show();
}
