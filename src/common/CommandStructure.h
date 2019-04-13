#pragma once

#include "Color.h"
#include "Position.h"
#include "../model/Unit.h"

struct CommandStructure
{

    CommandStructure() : undoFrom(Position(-1, -1)),
                         undoTo(Position(-1, -1)),
                         redoFrom(Position(-1, -1)),
                         redoTo(Position(-1, -1)),
                         hasCapturedUnit(false)
    {
    }

    Position undoFrom;
    Position undoTo;
    Position redoFrom;
    Position redoTo;
    bool hasCapturedUnit;
    color_t capturedUnitColor;
    unitType_t capturedUnitType;
};
