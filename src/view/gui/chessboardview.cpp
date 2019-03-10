#include "chessboardview.h"
#include "ui_chessboardview.h"

chessBoardView::chessBoardView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chessBoardView)
{
    ui->setupUi(this);
}

chessBoardView::~chessBoardView()
{
    delete ui;
}
