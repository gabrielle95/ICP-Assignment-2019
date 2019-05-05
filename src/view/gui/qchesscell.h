/*
 * @file qchescell.h
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
#ifndef QCHESSCELL_H
#define QCHESSCELL_H

#include <QPushButton>
#include "styles.h"
#include "../../common/Color.h"

/**
 * @brief Class corresponding to a gui cell
 *
 */
class QChessCell : public QPushButton
{
    Q_OBJECT
  public:

    /**
     * @brief Construct a new QChessCell object
     *
     * @param color The background color of the cell
     * @param parent The parrent widget
     */
    QChessCell(color_t color, QWidget *parent = 0);

    /**
     * @brief Gets the background style
     *
     * @return QString The background style
     */
    QString backgroundStyle() const
    {
        return backgroundStyle_;
    }

    /**
     * @brief Set the unit style
     *
     * @param unitStyle The style to set
     */
    void setUnitStyle(QString unitStyle)
    {
        this->unitStyle_ = unitStyle;
    }

    /**
     * @brief Clear the unit style
     *
     */
    void unsetUnitStyle()
    {
        this->unitStyle_.clear();
    }

    /**
     * @brief Checks if the cell contains any unit style
     *
     * @return true The cell has a unit style
     * @return false The cell doesnt have a unit style
     */
    bool hasUnitStyle() const
    {
        return !this->unitStyle_.isEmpty();
    }

    /**
     * @brief Get the Unit Style of a cell
     *
     * @return QString The corresponding unit style
     */
    QString getUnitStyle() const
    {
        return this->unitStyle_;
    }

    /**
     * @brief Set the Background Style of a cell
     *
     * @param bgStyle The background style
     */
    void setBackgroundStyle(QString bgStyle)
    {
        this->backgroundStyle_ = bgStyle;
    }

    /**
     * @brief Apply stylesheet with set styles
     *
     */
    void draw()
    {
        QString selStyle;

        if (this->isChecked())
            selStyle = Styles::cellSelectedBg;
        if (this->availableForMove())
            selStyle = Styles::cellAllowedMoveBg;
        this->setStyleSheet(this->backgroundStyle_ + this->unitStyle_ + selStyle);
    }

    /**
     * @brief Checks if the cell is available to move
     *
     * @return true The cell is available to move
     * @return false The cell is not available to move
     */
    bool availableForMove() const
    {
        return this->availableForMove_;
    }

    /**
     * @brief Set the cell available to move
     *
     * @param value The truth value of the flag
     */
    void setAvailableForMove(bool value)
    {
        this->availableForMove_ = value;
    }

    /**
     * @brief Set if this cell is used for captured units
     *
     * @param value The truth value of the cell used for capture
     */
    void setCaptured(bool value)
    {
        this->captured_ = value;
    }

    /**
     * @brief Checks if this cell is used for captured units
     *
     * @return true Cell is used for captured units
     * @return false Cell is not used for captured units
     */
    bool isCaptured() const
    {
        return this->captured_;
    }

  signals:
    void sig_emitCellSelectionChanged(QChessCell *from, QChessCell *to);
    void sig_emitRequestAvailableCells();

  private:
    color_t color_;
    QWidget *parent_;
    QString backgroundStyle_;
    QString unitStyle_;
    bool availableForMove_;
    bool captured_;
};

#endif // QCHESSCELL_H
