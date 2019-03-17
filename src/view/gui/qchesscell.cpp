#include "qchesscell.h"

QChessCell::QChessCell(color_t color, QWidget *parent) :
    QPushButton(parent),
    color_(color),
    parent_(parent),
    selected_(false)
{
    this->setCheckable(true);

    if(color == BLACK) {
        this->backgroundStyle_ = "background-color: rgb(50, 50, 50);";
    }
    else if(color == WHITE) {
        this->backgroundStyle_ = "background-color: rgb(255, 255, 255);";
    }

    this->setStyleSheet(backgroundStyle_);
    unitStyle_ = "";
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void QChessCell::onSelectionChange(QChessCell *cell) {

    QString unselectedStyle = backgroundStyle_ + unitStyle_;
    if(cell == this) {
        if(!selected_) {
            this->setStyleSheet(this->styleSheet() + Styles::cellSelectedBg);
            selected_ = true;
        }
        else {
           this->setStyleSheet(unselectedStyle);
            selected_ = false;
        }
    }
    else {
        this->setStyleSheet(unselectedStyle);
        selected_ = false;
    }
}
