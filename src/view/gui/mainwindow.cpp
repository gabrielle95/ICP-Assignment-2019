#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "chessboardview.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow),
                                          gameNumber(0)
{
    application = std::make_unique<Application>();

    ui->setupUi(this);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
    int gameToDelete = gameIds.at(index);
    application->quitGame(gameToDelete);
    gameIds.erase(gameIds.begin() + index);
}

void MainWindow::on_addtab_btn_clicked()
{
    chessBoardView *c = new chessBoardView(gameNumber);
    ui->tabWidget->addTab(c, QString("Game %0").arg(gameNumber));
    connect(c, SIGNAL(sig_emitMoveRequest(Position, Position)), this, SLOT(sl_onMoveRequest(Position, Position)));
    connect(c, SIGNAL(sig_emitAvailableCellsRequest(Position)), this, SLOT(sl_onRequestAvailableCells(Position)));

    application->newGame(gameNumber);
    gameIds.push_back(gameNumber);
    gameNumber += 1;
}

void MainWindow::sl_onMoveRequest(Position from, Position to)
{
    chessBoardView *senderView = (chessBoardView *)sender();
    if (application->onRequestMove(senderView->Id(), from, to))
    {
        senderView->executePendingMove();
    }
}

void MainWindow::sl_onRequestAvailableCells(Position from)
{
    chessBoardView *senderView = (chessBoardView *)sender();
    senderView->markAvailableCellsForMove(application->onRequestAvailableCells(senderView->Id(), from));
    //APPLICATION ON REQUEST CELLS
}
