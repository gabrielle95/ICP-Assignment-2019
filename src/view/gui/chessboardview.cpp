#include "chessboardview.h"
#include "ui_chessboardview.h"

chessBoardView::chessBoardView(int id, QWidget *parent) : id_(id),
                                                          QWidget(parent),
                                                          ui(new Ui::chessBoardView),
                                                          pendingFrom(nullptr),
                                                          pendingTo(nullptr)
{
    ui->setupUi(this);
    auto grid = ui->gridLayout;

    bool black = false;

    for (int i = 1, col = A; i < grid->columnCount() - 1, col <= H; i++, col++)
    {
        for (int j = 1, row = EIGHT; j < grid->rowCount() - 1, row >= ONE; j++, row--)
        {

            QChessCell *cell;

            black ? cell = new QChessCell(BLACK, this)
                  : cell = new QChessCell(WHITE, this);

            grid->addWidget(cell, j, i);
            qCellBoard_.at(col).at(row) = cell;
            connect(cell, SIGNAL(clicked(bool)), this, SLOT(sl_cellWasClicked()));
            connect(this, SIGNAL(sig_emitClickedCell(QChessCell *)), cell, SLOT(sl_onReceiveClick(QChessCell *)));
            connect(cell, SIGNAL(sig_emitCellSelectionChanged(QChessCell *, QChessCell *)), this, SLOT(sl_cellSelectionWasChanged(QChessCell *, QChessCell *)));
            connect(cell, SIGNAL(sig_emitRequestAvailableCells()), this, SLOT(sl_onRequestAvailableCells()));

            black = !black;
        }
        black = !black;
    }

    initStyles_();

    //the captured container is there
    QChessCell *cell = new QChessCell(WHITE, this); //dummy
    ui->formLayout->addWidget(cell);

    draw();
}

chessBoardView::~chessBoardView()
{
    delete ui;
}

void chessBoardView::executePendingMove()
{
    if (!pendingFrom || !pendingTo)
        return;
    pendingTo->setUnitStyle(pendingFrom->getUnitStyle());
    pendingFrom->unsetUnitStyle();
    pendingTo->setChecked(false);
    pendingTo->setCheckable(true);
    pendingFrom->setCheckable(false);

    clearAvailableForMove_();
}

void chessBoardView::markAvailableCellsForMove(std::vector<Position> cellPositions)
{

    clearAvailableForMove_();

    for (auto &p : cellPositions)
    {
        qCellBoard_.at(p.clm()).at(p.row())->setAvailableForMove(true);
    }
}

void chessBoardView::draw()
{
    for (int col = A; col <= H; col++)
    {
        for (int row = ONE; row <= EIGHT; row++)
        {
            qCellBoard_.at(col).at(row)->draw();
        }
    }
}

void chessBoardView::sl_cellWasClicked()
{
    QChessCell *cell = (QChessCell *)sender();
    emit sig_emitClickedCell(cell);
    draw();
}

void chessBoardView::sl_cellSelectionWasChanged(QChessCell *from, QChessCell *to)
{

    if (to == nullptr)
    {
        clearAvailableForMove_();
        return;
    }

    pendingFrom = from;
    pendingTo = to;
    emit sig_emitMoveRequest(getCellPosition_(from), getCellPosition_(to));
}

void chessBoardView::sl_onRequestAvailableCells()
{
    QChessCell *requestingCell = (QChessCell *)sender();
    emit sig_emitAvailableCellsRequest(getCellPosition_(requestingCell));
    // TODO SIGNAL TO REQUEST AVAILABLE POSITIONS
    // CACHE IT ON BACKEND
}

void chessBoardView::initStyles_()
{

    /******** WHITE ********/
    qCellBoard_.at(A).at(TWO)->setUnitStyle(Styles::cellPawnWhiteFg);
    qCellBoard_.at(B).at(TWO)->setUnitStyle(Styles::cellPawnWhiteFg);
    qCellBoard_.at(C).at(TWO)->setUnitStyle(Styles::cellPawnWhiteFg);
    qCellBoard_.at(D).at(TWO)->setUnitStyle(Styles::cellPawnWhiteFg);
    qCellBoard_.at(E).at(TWO)->setUnitStyle(Styles::cellPawnWhiteFg);
    qCellBoard_.at(F).at(TWO)->setUnitStyle(Styles::cellPawnWhiteFg);
    qCellBoard_.at(G).at(TWO)->setUnitStyle(Styles::cellPawnWhiteFg);
    qCellBoard_.at(H).at(TWO)->setUnitStyle(Styles::cellPawnWhiteFg);

    qCellBoard_.at(A).at(ONE)->setUnitStyle(Styles::cellRookWhiteFg);
    qCellBoard_.at(H).at(ONE)->setUnitStyle(Styles::cellRookWhiteFg);

    qCellBoard_.at(B).at(ONE)->setUnitStyle(Styles::cellKnightWhiteFg);
    qCellBoard_.at(G).at(ONE)->setUnitStyle(Styles::cellKnightWhiteFg);

    qCellBoard_.at(C).at(ONE)->setUnitStyle(Styles::cellBishopWhiteFg);
    qCellBoard_.at(F).at(ONE)->setUnitStyle(Styles::cellBishopWhiteFg);

    qCellBoard_.at(D).at(ONE)->setUnitStyle(Styles::cellQueenWhiteFg);
    qCellBoard_.at(E).at(ONE)->setUnitStyle(Styles::cellKingWhiteFg);

    /******** BLACK ********/
    qCellBoard_.at(A).at(SEVEN)->setUnitStyle(Styles::cellPawnBlackFg);
    qCellBoard_.at(B).at(SEVEN)->setUnitStyle(Styles::cellPawnBlackFg);
    qCellBoard_.at(C).at(SEVEN)->setUnitStyle(Styles::cellPawnBlackFg);
    qCellBoard_.at(D).at(SEVEN)->setUnitStyle(Styles::cellPawnBlackFg);
    qCellBoard_.at(E).at(SEVEN)->setUnitStyle(Styles::cellPawnBlackFg);
    qCellBoard_.at(F).at(SEVEN)->setUnitStyle(Styles::cellPawnBlackFg);
    qCellBoard_.at(G).at(SEVEN)->setUnitStyle(Styles::cellPawnBlackFg);
    qCellBoard_.at(H).at(SEVEN)->setUnitStyle(Styles::cellPawnBlackFg);

    qCellBoard_.at(A).at(EIGHT)->setUnitStyle(Styles::cellRookBlackFg);
    qCellBoard_.at(H).at(EIGHT)->setUnitStyle(Styles::cellRookBlackFg);

    qCellBoard_.at(B).at(EIGHT)->setUnitStyle(Styles::cellKnightBlackFg);
    qCellBoard_.at(G).at(EIGHT)->setUnitStyle(Styles::cellKnightBlackFg);

    qCellBoard_.at(C).at(EIGHT)->setUnitStyle(Styles::cellBishopBlackFg);
    qCellBoard_.at(F).at(EIGHT)->setUnitStyle(Styles::cellBishopBlackFg);

    qCellBoard_.at(D).at(EIGHT)->setUnitStyle(Styles::cellQueenBlackFg);
    qCellBoard_.at(E).at(EIGHT)->setUnitStyle(Styles::cellKingBlackFg);

    for (int col = A; col <= H; col++)
    {
        for (int row = ONE, rrow = EIGHT; row <= TWO, rrow >= SEVEN; row++, rrow--)
        {
            qCellBoard_.at(col).at(row)->setCheckable(true);
            qCellBoard_.at(col).at(rrow)->setCheckable(true);
        }
    }
}

Position chessBoardView::getCellPosition_(QChessCell *cell)
{
    for (int col = A; col <= H; col++)
    {
        for (int row = ONE; row <= EIGHT; row++)
        {
            if (qCellBoard_.at(col).at(row) == cell)
            {
                return Position((letter_t)col, (rowPos_t)row);
            }
        }
    }
}

void chessBoardView::clearAvailableForMove_()
{
    for (auto &a : qCellBoard_)
    {
        for (auto &cell : a)
        {
            cell->setAvailableForMove(false);
        }
    }
}
