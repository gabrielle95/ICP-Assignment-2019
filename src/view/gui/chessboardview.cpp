#include "chessboardview.h"
#include "ui_chessboardview.h"

chessBoardView::chessBoardView(int id, QWidget *parent) : QWidget(parent),
                                                          ui(new Ui::chessBoardView),
                                                          id_(id),
                                                          pendingFrom(nullptr),
                                                          pendingTo(nullptr),
                                                          previouslyClickedCell(nullptr),
                                                          itsWhitesTurn_(true)
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

            // connect the click signal from the cell
            connect(cell, SIGNAL(clicked(bool)), this, SLOT(sl_cellWasClicked()));

            black = !black;
        }
        black = !black;
    }

    initStyles_();

    //the captured container is there
    QChessCell *cell = new QChessCell(WHITE, this); //dummy
    ui->formLayout->addWidget(cell);


    // app buttons
    QPushButton *openButton = new QPushButton();
    openButton->setStyleSheet(Styles::openIcon);
    openButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->appButtonsLayout->addWidget(openButton);

    QPushButton *saveButton = new QPushButton();
    saveButton->setStyleSheet(Styles::saveIcon);
    saveButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->appButtonsLayout->addWidget(saveButton);

    QPushButton *undoButton = new QPushButton();
    undoButton->setStyleSheet(Styles::undoIcon);
    undoButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->appButtonsLayout->addWidget(undoButton);

    connect(undoButton, SIGNAL(clicked(bool)), this, SLOT(sl_undoClicked()));

    QPushButton *redoButton = new QPushButton();
    redoButton->setStyleSheet(Styles::redoIcon);
    redoButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->appButtonsLayout->addWidget(redoButton);

    draw();
}

chessBoardView::~chessBoardView()
{
    delete ui;
}

void chessBoardView::executePendingMove()
{
    if (!pendingFrom || !pendingTo) {
        return;
    }

    pendingTo->setUnitStyle(pendingFrom->getUnitStyle());
    pendingFrom->unsetUnitStyle();
    pendingTo->setChecked(false);
    pendingTo->setCheckable(true);
    pendingFrom->setCheckable(false);

    clearAvailableForMove_();

    // move executed successfully, so switch to other players color
    itsWhitesTurn_ = !itsWhitesTurn_;
    emit sig_emitRequestUnitsOnTurn(itsWhitesTurn_);
}

void chessBoardView::executeUndoMove(CommandStructure data) {
    if(data.undoFrom.isValid() && data.undoTo.isValid()) {
        QChessCell *from = qCellBoard_.at(data.undoFrom.clm()).at(data.undoFrom.row());
        QChessCell * to = qCellBoard_.at(data.undoTo.clm()).at(data.undoTo.row());
        to->setUnitStyle(from->getUnitStyle());
        from->unsetUnitStyle();
        to->setChecked(false);
        from->setCheckable(false);
        to->setCheckable(true);

        if(data.hasCapturedUnit) {
            //to = from;
            //TODO restore captured unit
        }
        itsWhitesTurn_ = !itsWhitesTurn_;
        emit sig_emitRequestUnitsOnTurn(itsWhitesTurn_);
    }
    draw();
}

void chessBoardView::markAvailableCellsForMove(std::vector<Position> cellPositions)
{

    clearAvailableForMove_();

    for (auto &p : cellPositions)
    {
        qCellBoard_.at(p.clm()).at(p.row())->setAvailableForMove(true);
    }
}

void chessBoardView::setTheseCellsCheckable(std::vector<Position> positions) {
    for (auto &a : qCellBoard_)
        {
            for (auto &cell : a)
            {
                cell->setCheckable(false);
            }
        }

    for (auto &p : positions)
    {
        qCellBoard_.at(p.clm()).at(p.row())->setCheckable(true);
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
    QChessCell *clickedCell = (QChessCell *)sender();

    // no cell is checked before clickedCell is clicked
    if(previouslyClickedCell == nullptr || !previouslyClickedCell->isChecked()) {
        // we clicked on a cell, none selected before
        if(clickedCell->isChecked()){
            //we will request available moves for this cell
            onRequestAvailableMoves(clickedCell);
        }
        else {
            //we are now unchecking this checked cell, so we must clean its moves too
            clearAvailableForMove_();
        }

        // save previously clicked cell
        previouslyClickedCell = clickedCell;

    } //if previously clicked cell is selected
    else if(previouslyClickedCell->isChecked()) {
        //if we now clicked on a friendly cell
        if(clickedCell->isCheckable()) {
            //we will uncheck the previous cell
            previouslyClickedCell->setChecked(false);
            //we will also clear its available moves
            clearAvailableForMove_();
            //and request available moves for the clicked cell if checked
            if(clickedCell->isChecked()) {
                onRequestAvailableMoves(clickedCell);
            }

            // save previously clicked cell
            previouslyClickedCell = clickedCell;
        } // now if the clicked cell is empty or unfriendly
        else {
            // we will try to move the figure
            onCellSelectionChanged(previouslyClickedCell, clickedCell);

            // and then clean up selection states
            previouslyClickedCell->setChecked(false);
            clearAvailableForMove_();
            previouslyClickedCell = nullptr;
        }
    }

    draw();
}

void chessBoardView::sl_undoClicked() {
    emit sig_emitRequestUndo();
}

void chessBoardView::onCellSelectionChanged(QChessCell *from, QChessCell *to) {
    /* sends request to the 'backend' */
    pendingFrom = from;
    pendingTo = to;
    emit sig_emitMoveRequest(getCellPosition_(from), getCellPosition_(to));
}

void chessBoardView::onRequestAvailableMoves(QChessCell *from) {
    emit sig_emitAvailableCellsRequest(getCellPosition_(from));
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

    // on init we cant use a signal for this, as it is connected later
    // whites turn first
    for (int col = A; col <= H; col++)
    {
        for (int row = ONE; row <= TWO; row++)
        {
            qCellBoard_.at(col).at(row)->setCheckable(true);
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

    return Position(-1, -1);
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
