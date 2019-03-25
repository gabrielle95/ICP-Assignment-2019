#include "qchesscell.h"

QChessCell::QChessCell(color_t color, QWidget *parent) :
    QPushButton(parent),
    color_(color),
    parent_(parent),
    selected_(false)
{
    if(color == BLACK) {
        this->backgroundStyle_ = "background-color: rgb(50, 50, 50);";
    }
    else if(color == WHITE) {
        this->backgroundStyle_ = "background-color: rgb(255, 255, 255);";
    }

    setBackgroundStyle(backgroundStyle_);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void QChessCell::sl_onReceiveClick(QChessCell *clickedCell) {
    if(clickedCell != this && this->isChecked()) {
        this->setChecked(false);
        emit sig_emitCellSelectionChanged(this, clickedCell);
    }
}
