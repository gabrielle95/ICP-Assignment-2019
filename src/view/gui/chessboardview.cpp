#include "chessboardview.h"
#include "ui_chessboardview.h"

chessBoardView::chessBoardView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chessBoardView)
{
    ui->setupUi(this);
    auto grid = ui->gridLayout;

    bool black = false;

    for(int i = 1, col = 7; i < grid->columnCount()-1, col >= 0; i++, col --) {
        for(int j = 1, row = 7; j < grid->rowCount()-1, row >= 0; j++, row--) {

            QChessCell *cell;

            black ? cell = new QChessCell(BLACK, this)
                  : cell = new QChessCell(WHITE, this);

            grid->addWidget(cell, j, i);
            qCellBoard_.at(col).at(row) = cell;
            connect(cell, SIGNAL(clicked(bool)), this, SLOT(cellClicked()));
            connect(this, SIGNAL(cellSelectionChanged(QChessCell *)), cell, SLOT(onSelectionChange(QChessCell *)) );
            black = !black;
        }
        black = !black;
    }
}

chessBoardView::~chessBoardView()
{
    delete ui;
}

void chessBoardView::cellClicked() {
    QChessCell *cell = (QChessCell *)sender();
    emit cellSelectionChanged(cell);
}
