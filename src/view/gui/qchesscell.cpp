/*
 * @file qchescell.cpp
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
#include "qchesscell.h"

QChessCell::QChessCell(color_t color, QWidget *parent) : QPushButton(parent),
                                                         color_(color),
                                                         parent_(parent),
                                                         availableForMove_(false),
                                                         captured_(false)
{
    if (color == BLACK)
    {
        this->backgroundStyle_ = "background-color: rgb(50, 50, 50);";
    }
    else if (color == WHITE)
    {
        this->backgroundStyle_ = "background-color: rgb(255, 255, 255);";
    }

    setBackgroundStyle(backgroundStyle_);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}
