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
    ui->tabWidget->setVisible(false);
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

    if (ui->tabWidget->count() == 0)
    {
        ui->tabWidget->setVisible(false);
        ui->welcomeLabel->setVisible(true);
    }
}

void MainWindow::on_addtab_btn_clicked()
{
    if (!ui->tabWidget->isVisible())
        ui->tabWidget->setVisible(true);
    if (ui->welcomeLabel->isVisible())
        ui->welcomeLabel->setVisible(false);

    chessBoardView *c = new chessBoardView(gameNumber);

    ui->tabWidget->addTab(c, QString("Game %0").arg(gameNumber));

    /* CONNECT VIEW SLOTS HERE*/
    connect(c, SIGNAL(sig_emitMoveRequest(Position, Position)), this, SLOT(sl_onMoveRequest(Position, Position)));
    connect(c, SIGNAL(sig_emitAvailableCellsRequest(Position)), this, SLOT(sl_onRequestAvailableCells(Position)));
    connect(c, SIGNAL(sig_emitRequestUnitsOnTurn(bool)), this, SLOT(sl_onRequestUnitsOnTurn(bool)));
    connect(c, SIGNAL(sig_emitRequestUndo()), this, SLOT(sl_onRequestUndo()));
    connect(c, SIGNAL(sig_emitRequestRedo()), this, SLOT(sl_onRequestRedo()));
    connect(c, SIGNAL(sig_emitRequestSerializedData()), this, SLOT(sl_onRequestSerializedData()));
    connect(c, SIGNAL(sig_emitRequestDeserializedData()), this, SLOT(sl_onRequestDeserializedData()));
    connect(c, SIGNAL(sig_emitRequestForward()), this, SLOT(sl_onRequestForward()));
    connect(c, SIGNAL(sig_emitRequestBackward()), this, SLOT(sl_onRequestBackward()));

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
}

void MainWindow::sl_onRequestUnitsOnTurn(bool isWhitesTurn)
{
    chessBoardView *senderView = (chessBoardView *)sender();
    senderView->setTheseCellsCheckable(application->onRequestPositionsOfPlayersTurn(senderView->Id(), isWhitesTurn));
}

void MainWindow::sl_onRequestUndo()
{
    chessBoardView *senderView = (chessBoardView *)sender();
    senderView->executeUndoMove(application->onRequestUndo(senderView->Id()));
}

void MainWindow::sl_onRequestRedo()
{
    chessBoardView *senderView = (chessBoardView *)sender();
    senderView->executeRedoMove(application->onRequestRedo(senderView->Id()));
}

void MainWindow::sl_onRequestSerializedData()
{
    chessBoardView *senderView = (chessBoardView *)sender();
    senderView->setSerializedData(application->onRequestSerializedData(senderView->Id()));
}

void MainWindow::sl_onRequestDeserializedData()
{
    chessBoardView *senderView = (chessBoardView *)sender();
    application->onRequestDeserializedData(senderView->Id(), senderView->getSerializedData());
}

void MainWindow::sl_onRequestForward()
{
    chessBoardView *senderView = (chessBoardView *)sender();
    senderView->executeRedoMove(application->onRequestForward(senderView->Id()));
}

void MainWindow::sl_onRequestBackward()
{
    chessBoardView *senderView = (chessBoardView *)sender();
    senderView->executeUndoMove(application->onRequestBackward(senderView->Id()));
}
