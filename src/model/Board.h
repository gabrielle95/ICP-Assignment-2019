#pragma once

#include <memory>
#include "Unit.h"

const int BOARD_LENGTH = 8;
const int UNIT_CAPACITY = 32;

using unitArray_t = std::array<unitPtr_t, UNIT_CAPACITY>;
using unit2DArray_t = std::array<unitPtr_t, BOARD_LENGTH>;
using unitBoardArray_t = std::array<unit2DArray_t, BOARD_LENGTH>;

using boardPtr_t = std::shared_ptr<class Board>;

class Board {

    public:

        Board();

        unitPtr_t At(letter_t clm, rowPos_t row);
        unitPtr_t At(Position pos);

    private:

        unitArray_t playingUnits_;
        unitArray_t capturedUnits_;

        unitBoardArray_t board_;

};