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

    QString backgroundStyle() const
    {
        return backgroundStyle_;
    }

    void setUnitStyle(QString unitStyle)
    {
        this->unitStyle_ = unitStyle;
    }

    void unsetUnitStyle()
    {
        this->unitStyle_.clear();
    }

    QString getUnitStyle() const
    {
        return this->unitStyle_;
    }

    void setBackgroundStyle(QString bgStyle)
    {
        this->backgroundStyle_ = bgStyle;
    }

    void draw()
    {
        QString selStyle;

        if (this->isChecked())
            selStyle = Styles::cellSelectedBg;
        if (this->availableForMove())
            selStyle = Styles::cellAllowedMoveBg;
        this->setStyleSheet(this->backgroundStyle_ + this->unitStyle_ + selStyle);
    }

    bool availableForMove() const
    {
        return this->availableForMove_;
    }

    void setAvailableForMove(bool value)
    {
        this->availableForMove_ = value;
    }

  signals:
    void sig_emitCellSelectionChanged(QChessCell *from, QChessCell *to);
    void sig_emitRequestAvailableCells();

  private slots:
    void sl_onReceiveClick(QChessCell *clickedCell);

  private:
    color_t color_;
    QWidget *parent_;
    QString backgroundStyle_;
    QString unitStyle_;
    bool availableForMove_;
};

#endif // QCHESSCELL_H
