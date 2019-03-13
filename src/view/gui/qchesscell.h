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

    void setSelectedForAction (bool value) {
        selected_ = value;
    }


private slots:
    void onSelectionChange(QChessCell * cell);

private:
    color_t color_;
    QWidget *parent_;
    QString backgroundStyle_;
    bool selected_;
};

#endif // QCHESSCELL_H
