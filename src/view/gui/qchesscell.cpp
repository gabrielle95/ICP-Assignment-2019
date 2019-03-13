#include "qchesscell.h"

QChessCell::QChessCell(color_t color, QWidget *parent) :
    QPushButton(parent),
    color_(color),
    parent_(parent),
    selected_(false)
{
    this->setCheckable(true);

    if(color == BLACK) {
        this->backgroundStyle_ = "background-color: rgb(0, 0, 0);";
        this->setStyleSheet(backgroundStyle_);
    }
    else {
        this->backgroundStyle_ = "background-color: rgb(255, 255, 255);";
        this->setStyleSheet(backgroundStyle_);
    }

    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void QChessCell::onSelectionChange(QChessCell *cell) {
    if(cell != this) {
        this->setStyleSheet(this->backgroundStyle());
        return;
    }
    this->setStyleSheet(Styles::cellSelectedBg + Styles::cellRookWhiteFg);
}
