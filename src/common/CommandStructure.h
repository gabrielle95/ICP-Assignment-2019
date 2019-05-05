/*
 * @file CommandStructure.h
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
#pragma once

#include "Color.h"
#include "Position.h"
#include "../model/Unit.h"

/**
 * @brief A data structure that is being sent to gui to represent various moves graphically
 *
 */
struct CommandStructure
{

    /**
     * @brief Construct a new Command Structure object
     *
     */
    CommandStructure() : undoFrom(Position(-1, -1)),
                         undoTo(Position(-1, -1)),
                         redoFrom(Position(-1, -1)),
                         redoTo(Position(-1, -1)),
                         from(Position(-1, -1)),
                         to(Position(-1, -1)),
                         hasCapturedUnit(false)
    {
    }

    Position undoFrom;
    Position undoTo;
    Position redoFrom;
    Position redoTo;
    Position from;
    Position to;
    bool hasCapturedUnit;
    color_t capturedUnitColor;
    unitType_t capturedUnitType;
};
