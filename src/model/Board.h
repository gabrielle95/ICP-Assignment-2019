#pragma once

#include <memory>
#include <algorithm>
#include "Unit.h"
#include "Rules.h"

const int BOARD_LENGTH = 8;
const int UNIT_CAPACITY = 32;

using unitArray_t = std::array<unitPtr_t, UNIT_CAPACITY>;
using unitBoardArray_t = std::array<std::array<unitPtr_t, BOARD_LENGTH>, BOARD_LENGTH>;

using boardPtr_t = std::shared_ptr<class Board>;

class Board {

    public:

        Board();

        unitPtr_t At(letter_t clm, rowPos_t row);
        unitPtr_t At(Position pos);
        void print ();
        bool checkMoveValidity(unitType_t unitType, Position fromPos, Position toPos);
        void moveUnit(unitPtr_t unit, Position from, Position to); //TODO

    private:

        unitArray_t playingUnits_; // ?
        unitArray_t capturedUnits_; // ?

        unitBoardArray_t board_;
};