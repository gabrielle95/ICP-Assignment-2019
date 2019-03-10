#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "chessboardview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);
    ui->tabWidget->addTab(new chessBoardView(), QString("Game %0").arg(ui->tabWidget->count() + 1));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_addtab_btn_clicked()
{
    ui->tabWidget->addTab(new chessBoardView(), QString("Game %0").arg(ui->tabWidget->count() + 1));
}
