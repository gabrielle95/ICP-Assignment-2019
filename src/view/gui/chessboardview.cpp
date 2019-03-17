#include "chessboardview.h"
#include "ui_chessboardview.h"

chessBoardView::chessBoardView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chessBoardView)
{
    ui->setupUi(this);
    auto grid = ui->gridLayout;

    bool black = false;

    for(int i = 1, col = A; i < grid->columnCount()-1, col <= H; i++, col ++) {
        for(int j = 1, row = EIGHT; j < grid->rowCount()-1, row >= ONE; j++, row--) {

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

    initStyles_();

    //the container is there
    QChessCell *cell = new QChessCell(WHITE, this);
    ui->formLayout->addWidget(cell);
}

chessBoardView::~chessBoardView() {
    delete ui;
}

void chessBoardView::cellClicked() {
    QChessCell *cell = (QChessCell *)sender();
    emit cellSelectionChanged(cell);
}

void chessBoardView::initStyles_() {

        /******** WHITE ********/
        qCellBoard_.at(A).at(TWO)->drawUnit(Styles::cellPawnWhiteFg);
        qCellBoard_.at(B).at(TWO)->drawUnit(Styles::cellPawnWhiteFg);
        qCellBoard_.at(C).at(TWO)->drawUnit(Styles::cellPawnWhiteFg);
        qCellBoard_.at(D).at(TWO)->drawUnit(Styles::cellPawnWhiteFg);
        qCellBoard_.at(E).at(TWO)->drawUnit(Styles::cellPawnWhiteFg);
        qCellBoard_.at(F).at(TWO)->drawUnit(Styles::cellPawnWhiteFg);
        qCellBoard_.at(G).at(TWO)->drawUnit(Styles::cellPawnWhiteFg);
        qCellBoard_.at(H).at(TWO)->drawUnit(Styles::cellPawnWhiteFg);

        qCellBoard_.at(A).at(ONE)->drawUnit(Styles::cellRookWhiteFg);
        qCellBoard_.at(H).at(ONE)->drawUnit(Styles::cellRookWhiteFg);

        qCellBoard_.at(B).at(ONE)->drawUnit(Styles::cellKnightWhiteFg);
        qCellBoard_.at(G).at(ONE)->drawUnit(Styles::cellKnightWhiteFg);

        qCellBoard_.at(C).at(ONE)->drawUnit(Styles::cellBishopWhiteFg);
        qCellBoard_.at(F).at(ONE)->drawUnit(Styles::cellBishopWhiteFg);

        qCellBoard_.at(D).at(ONE)->drawUnit(Styles::cellQueenWhiteFg);
        qCellBoard_.at(E).at(ONE)->drawUnit(Styles::cellKingWhiteFg);

        /******** BLACK ********/
        qCellBoard_.at(A).at(SEVEN)->drawUnit(Styles::cellPawnBlackFg);
        qCellBoard_.at(B).at(SEVEN)->drawUnit(Styles::cellPawnBlackFg);
        qCellBoard_.at(C).at(SEVEN)->drawUnit(Styles::cellPawnBlackFg);
        qCellBoard_.at(D).at(SEVEN)->drawUnit(Styles::cellPawnBlackFg);
        qCellBoard_.at(E).at(SEVEN)->drawUnit(Styles::cellPawnBlackFg);
        qCellBoard_.at(F).at(SEVEN)->drawUnit(Styles::cellPawnBlackFg);
        qCellBoard_.at(G).at(SEVEN)->drawUnit(Styles::cellPawnBlackFg);
        qCellBoard_.at(H).at(SEVEN)->drawUnit(Styles::cellPawnBlackFg);

        qCellBoard_.at(A).at(EIGHT)->drawUnit(Styles::cellRookBlackFg);
        qCellBoard_.at(H).at(EIGHT)->drawUnit(Styles::cellRookBlackFg);

        qCellBoard_.at(B).at(EIGHT)->drawUnit(Styles::cellKnightBlackFg);
        qCellBoard_.at(G).at(EIGHT)->drawUnit(Styles::cellKnightBlackFg);

        qCellBoard_.at(C).at(EIGHT)->drawUnit(Styles::cellBishopBlackFg);
        qCellBoard_.at(F).at(EIGHT)->drawUnit(Styles::cellBishopBlackFg);

        qCellBoard_.at(D).at(EIGHT)->drawUnit(Styles::cellQueenBlackFg);
        qCellBoard_.at(E).at(EIGHT)->drawUnit(Styles::cellKingBlackFg);
}
