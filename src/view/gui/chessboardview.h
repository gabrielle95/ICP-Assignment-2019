#ifndef CHESSBOARDVIEW_H
#define CHESSBOARDVIEW_H

#include <array>
#include <QWidget>
#include "../../common/Position.h"
#include "styles.h"
#include "qchesscell.h"

const int MAX_CELLS = 8;

namespace Ui {
class chessBoardView;
}

class chessBoardView : public QWidget
{
    Q_OBJECT

public:
    explicit chessBoardView(int id, QWidget *parent = 0);
    ~chessBoardView();

    void draw();

    int Id() const {
        return this->id_;
    }

    void executePendingMove();
    void markAvailableCellsForMove(std::vector<Position> cellPositions);

signals:
    void sig_emitClickedCell(QChessCell *cell);
    void sig_emitMoveRequest(Position from, Position to);
    void sig_emitAvailableCellsRequest(Position from);

private slots:
    void sl_cellWasClicked();
    void sl_cellSelectionWasChanged(QChessCell *from, QChessCell* to);
    void sl_onRequestAvailableCells();

private:
    void initStyles_();
    void moveUnitStyle_();
    Position getCellPosition_(QChessCell *cell);

    Ui::chessBoardView *ui;
    std::array<std::array<QChessCell *, MAX_CELLS>, MAX_CELLS> qCellBoard_;
    int id_;

    QChessCell *pendingFrom;
    QChessCell *pendingTo;
};

#endif // CHESSBOARDVIEW_H
