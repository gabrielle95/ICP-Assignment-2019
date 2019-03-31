#pragma once

#include <memory>
#include <algorithm>
#include "Unit.h"
#include "Rules.h"

const int BOARD_LENGTH = 8;
const int UNIT_CAPACITY = 32;

using unitBoardArray_t = std::array<std::array<unitPtr_t, BOARD_LENGTH>, BOARD_LENGTH>;

using boardPtr_t = std::shared_ptr<class Board>;

class Board {

    public:

        Board();

        unitPtr_t At(letter_t clm, rowPos_t row);
        unitPtr_t At(Position pos);
        void print ();
        bool checkMoveValidity(unitPtr_t unit, Position fromPos, Position toPos);
        void moveUnit(unitPtr_t unit, Position to); //TODO
        void captureUnit(unitPtr_t unit);
        Position findUnitPosition(unitPtr_t unit);

    private:

        void setUnitTo_(unitPtr_t unit, Position pos);

        unitVector_t capturedUnits_; // ?

        unitBoardArray_t board_;
};