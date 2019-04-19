#ifndef CHESSBOARDVIEW_H
#define CHESSBOARDVIEW_H

#include <array>
#include <QWidget>
#include "../../common/Position.h"
#include "../../common/CommandStructure.h"
#include "styles.h"
#include "qchesscell.h"

const int MAX_CELLS = 8;
const int MAX_CAPTURED = 32;

namespace Ui
{
class chessBoardView;
}

class chessBoardView : public QWidget
{
    Q_OBJECT

  public:
    explicit chessBoardView(int id, QWidget *parent = 0);
    ~chessBoardView();

    void draw();

    int Id() const
    {
        return this->id_;
    }

    bool isWhitesTurn() const {
        return this->itsWhitesTurn_;
    }

    void executePendingMove();
    void markAvailableCellsForMove(std::vector<Position> cellPositions);
    void setTheseCellsCheckable(std::vector<Position> positions);
    void executeUndoMove(CommandStructure data);
    void executeRedoMove(CommandStructure data);

  signals:
    void sig_emitClickedCell(QChessCell *cell);
    void sig_emitMoveRequest(Position from, Position to);
    void sig_emitAvailableCellsRequest(Position from);
    void sig_emitRequestUnitsOnTurn(bool isWhitesTurn);
    void sig_emitRequestUndo();
    void sig_emitRequestRedo();

  private slots:
    void sl_cellWasClicked();
    void sl_undoClicked();
    void sl_redoClicked();
    void sl_saveGameToFile();
    void sl_openGameFromFile();

  private:
    void onCellSelectionChanged(QChessCell *from, QChessCell *to);
    void onRequestAvailableMoves(QChessCell *from);
    void initStyles_();
    void moveUnitStyle_();
    Position getCellPosition_(QChessCell *cell);
    void clearAvailableForMove_();
    QPushButton *generateAppButton_(QString style, QString tooltip);

    Ui::chessBoardView *ui;
    std::array<std::array<QChessCell *, MAX_CELLS>, MAX_CELLS> qCellBoard_;
    std::vector<QChessCell*> qCapturedBoard_;


    int id_;

    QChessCell *pendingFrom;
    QChessCell *pendingTo;

    QChessCell *previouslyClickedCell;

    bool itsWhitesTurn_;
};

#endif // CHESSBOARDVIEW_H
