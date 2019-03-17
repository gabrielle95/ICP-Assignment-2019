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
    explicit chessBoardView(QWidget *parent = 0);
    ~chessBoardView();

signals:
    void cellSelectionChanged(QChessCell * selected);


private slots:
    void cellClicked();

private:
    void initStyles_();
    Ui::chessBoardView *ui;
    std::array<std::array<QChessCell *, MAX_CELLS>, MAX_CELLS> qCellBoard_;
};

#endif // CHESSBOARDVIEW_H
