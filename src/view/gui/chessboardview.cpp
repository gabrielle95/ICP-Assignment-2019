/*
 * @file chessboardview.cpp
 *
 * Project name:
 * Chess 2019
 *
 * Description:
 * http://www.fit.vutbr.cz/study/courses/ICP/public/ICP-PRJ-zadani.html.cs
 *
 * Team:
 * @author Gabriela Pacakova (xpacak01)
 * @author Adam Lanicek (xlanic04)
 */
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
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
    commandCounter_ = 0;
    bool black = false;

    for (int i = 1, col = A; col <= H; i++, col++)
    {
        for (int j = 1, row = EIGHT; row >= ONE; j++, row--)
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

    int col = 1;

    for (int i = 0; i < 16; i++)
    {
        QChessCell *cell = new QChessCell(WHITE, this); //dummy
        cell->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        cell->setCaptured(true);
        ui->capturedUnitsLayout->addWidget(cell, i + 1, col);
        qCapturedBoard_.push_back(cell);
    }

    col = 2;
    for (int i = 0; i < 16; i++)
    {
        QChessCell *cell = new QChessCell(WHITE, this); //dummy
        cell->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        cell->setCaptured(true);
        ui->capturedUnitsLayout->addWidget(cell, i + 1, col);
        qCapturedBoard_.push_back(cell);
    }

    initStyles_();

    // app buttons
    //open
    QPushButton *btn = generateAppButton_(Styles::openIcon, "Open a game.");

    ui->appButtonsLayout->addWidget(btn);

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(sl_openGameFromFile()));
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(sl_requestDeserializedData()));

    //save
    btn = generateAppButton_(Styles::saveIcon, "Save a game.");

    ui->appButtonsLayout->addWidget(btn);

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(sl_requestSerializedData()));
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(sl_saveGameToFile()));

    //undo
    btn = generateAppButton_(Styles::undoIcon, "Undo a user-performed step.");

    ui->appButtonsLayout->addWidget(btn);

    //undo signal
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(sl_undoClicked()));

    //redo
    btn = generateAppButton_(Styles::redoIcon, "Redo a user-performed step.");

    ui->appButtonsLayout->addWidget(btn);

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(sl_redoClicked()));

    //forward
    btn = generateAppButton_(Styles::forwardIcon, "Move one recorded step forward.");

    ui->appButtonsLayout->addWidget(btn);

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(sl_forwardClicked()));

    //backward
    btn = generateAppButton_(Styles::backwardIcon, "Move one recorded step backward.");

    ui->appButtonsLayout->addWidget(btn);

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(sl_backwardClicked()));

    //restart
    btn = generateAppButton_(Styles::restartIcon, "Restart recorded steps to the beginning.");

    ui->appButtonsLayout->addWidget(btn);

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(sl_restartClicked()));

    //draw cell styles
    draw();
}

chessBoardView::~chessBoardView()
{
    delete ui;
}

void chessBoardView::executePendingMove()
{
    if (!pendingFrom || !pendingTo)
    {
        return;
    }

    if (pendingTo->hasUnitStyle())
    {
        for (auto &c : qCapturedBoard_)
        {
            if (!c->hasUnitStyle())
            {
                c->setUnitStyle(pendingTo->getUnitStyle());
                break;
            }
        }
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

void chessBoardView::executeUndoMove(CommandStructure data)
{
    if (data.undoFrom.isValid() && data.undoTo.isValid())
    {
        QChessCell *from = qCellBoard_.at(data.undoFrom.clm()).at(data.undoFrom.row());
        QChessCell *to = qCellBoard_.at(data.undoTo.clm()).at(data.undoTo.row());
        to->setUnitStyle(from->getUnitStyle());
        from->unsetUnitStyle();
        to->setChecked(false);
        from->setCheckable(false);
        to->setCheckable(true);

        if (data.hasCapturedUnit)
        {
            to = from;
            QString retrievedStyle = Styles::getStyleFrom(data.capturedUnitType, data.capturedUnitColor);
            to->setUnitStyle(retrievedStyle);

            for (auto &c : qCapturedBoard_)
            {
                if (c->getUnitStyle() == retrievedStyle)
                {
                    c->unsetUnitStyle();
                    break;
                }
            }
        }
        itsWhitesTurn_ = !itsWhitesTurn_;
        emit sig_emitRequestUnitsOnTurn(itsWhitesTurn_);
    }
    draw();
}

void chessBoardView::executeRedoMove(CommandStructure data)
{
    if (data.redoFrom.isValid() && data.redoTo.isValid())
    {
        pendingFrom = qCellBoard_.at(data.redoFrom.clm()).at(data.redoFrom.row());
        pendingTo = qCellBoard_.at(data.redoTo.clm()).at(data.redoTo.row());
        executePendingMove();
    }
    draw();
}

void chessBoardView::executeRestartSteps()
{
    //reset the board gui
    initStyles_();
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

void chessBoardView::setTheseCellsCheckable(std::vector<Position> positions)
{
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

    for (auto &c : qCapturedBoard_)
    {
        c->draw();
    }
}

void chessBoardView::onGameFinish()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("The chess game has ended.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void chessBoardView::sl_cellWasClicked()
{
    QChessCell *clickedCell = (QChessCell *)sender();

    // no cell is checked before clickedCell is clicked
    if (previouslyClickedCell == nullptr || !previouslyClickedCell->isChecked())
    {
        // we clicked on a cell, none selected before
        if (clickedCell->isChecked())
        {
            //we will request available moves for this cell
            onRequestAvailableMoves(clickedCell);
        }
        else
        {
            //we are now unchecking this checked cell, so we must clean its moves too
            clearAvailableForMove_();
        }

        // save previously clicked cell
        previouslyClickedCell = clickedCell;

    } //if previously clicked cell is selected
    else if (previouslyClickedCell->isChecked())
    {
        //if we now clicked on a friendly cell
        if (clickedCell->isCheckable())
        {
            //we will uncheck the previous cell
            previouslyClickedCell->setChecked(false);
            //we will also clear its available moves
            clearAvailableForMove_();
            //and request available moves for the clicked cell if checked
            if (clickedCell->isChecked())
            {
                onRequestAvailableMoves(clickedCell);
            }

            // save previously clicked cell
            previouslyClickedCell = clickedCell;
        } // now if the clicked cell is empty or unfriendly
        else
        {
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

void chessBoardView::sl_undoClicked()
{
    emit sig_emitRequestUndo();
}

void chessBoardView::sl_redoClicked()
{
    emit sig_emitRequestRedo();
}

void chessBoardView::sl_requestSerializedData()
{
    emit sig_emitRequestSerializedData();
}

void chessBoardView::sl_requestDeserializedData()
{
    emit sig_emitRequestDeserializedData();
}

void chessBoardView::sl_saveGameToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save ICP Game"), "",
                                                    tr("ICP Chess Game (*);;All Files (*)"));

    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);

        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file for writing"),
                                     file.errorString());
            return;
        }

        QTextStream out(&file);
        out << QString::fromStdString(serializedData_);
    }
}

void chessBoardView::sl_openGameFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open ICP Game"), "",
                                                    tr("ICP Chess Game (*);;All Files (*)"));

    if (fileName.isEmpty())
    {
        return;
    }
    else
    {
        serializedData_.clear();
        ui->textBrowser->setText("");

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file for reading"),
                                     file.errorString());
            return;
        }

        QString inputData;
        QTextStream in(&file);
        serializedData_.clear();
        inputData = in.readAll();

        serializedData_ = inputData.toStdString();

        // set new data to the text browser
        ui->textBrowser->setText(inputData);
        QTextCursor cursor = ui->textBrowser->textCursor();
        QTextBlockFormat f;
        f.setBackground(Qt::lightGray);
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.setBlockFormat(f);

        // reset the board gui
        initStyles_();
        draw();
    }
}

void chessBoardView::sl_forwardClicked()
{
    emit sig_emitRequestForward();
}

void chessBoardView::sl_backwardClicked()
{
    emit sig_emitRequestBackward();
}

void chessBoardView::sl_restartClicked()
{
    emit sig_emitRequestRestart();
}

void chessBoardView::onCellSelectionChanged(QChessCell *from, QChessCell *to)
{
    /* sends request to the 'backend' */
    pendingFrom = from;
    pendingTo = to;
    emit sig_emitMoveRequest(getCellPosition_(from), getCellPosition_(to));
}

void chessBoardView::onRequestAvailableMoves(QChessCell *from)
{
    emit sig_emitAvailableCellsRequest(getCellPosition_(from));
}

void chessBoardView::initStyles_()
{
    // reset all styles on board
    for (int col = A; col <= H; col++)
    {
        for (int row = ONE; row <= EIGHT; row++)
        {
            qCellBoard_.at(col).at(row)->unsetUnitStyle();
        }
    }

    // clear all styles on captured board

    for(auto &c: qCapturedBoard_) {
        c->unsetUnitStyle();
    }

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

QPushButton *chessBoardView::generateAppButton_(QString style, QString tooltip)
{
    QPushButton *button = new QPushButton();
    button->setToolTip(tooltip);
    button->setStyleSheet(""
                          "QPushButton {" +
                          style + Styles::margin10px + "}"
                                                       "QToolTip { color: #ffffff; background-color: #000000; border: 0px; }");
    button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    return button;
}
