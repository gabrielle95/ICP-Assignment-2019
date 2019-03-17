#ifndef QCHESSCELL_H
#define QCHESSCELL_H

#include <QPushButton>
#include "styles.h"
#include "../../common/Color.h"

class QChessCell : public QPushButton
{
    Q_OBJECT
public:
    QChessCell(color_t color, QWidget *parent = 0);

    QString backgroundStyle() const{
        return backgroundStyle_;
    }

    bool isSelected() const {
        return selected_;
    }

    void drawUnit(QString unitStyle) {
        if(!this->unitStyle_.isEmpty()) undrawUnit();
        this->setStyleSheet(this->styleSheet() + unitStyle);
        this->unitStyle_ = unitStyle;
    }

    void undrawUnit() {
        this->setStyleSheet(this->backgroundStyle_);
        this->unitStyle_ = "";
    }


private slots:
    void onSelectionChange(QChessCell * cell);

private:
    color_t color_;
    QWidget *parent_;
    QString backgroundStyle_;
    QString unitStyle_;
    bool selected_;
};

#endif // QCHESSCELL_H
