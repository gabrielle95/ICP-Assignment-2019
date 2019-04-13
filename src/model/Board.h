#pragma once

#include <memory>
#include <algorithm>
#include "Unit.h"
#include "Rules.h"

const int BOARD_LENGTH = 8;
const int UNIT_CAPACITY = 32;
const int COL_MIN = 0;
const int COL_MAX = 7;
const int ROW_MIN = 0;
const int ROW_MAX = 7;

using unitBoardArray_t = std::array<std::array<unitPtr_t, BOARD_LENGTH>, BOARD_LENGTH>;

using boardPtr_t = std::shared_ptr<class Board>;

class Board
{

  public:
    Board();

    unitPtr_t At(letter_t clm, rowPos_t row);
    unitPtr_t At(Position pos);
    void print();
    bool checkMoveValidity(unitPtr_t unit, Position fromPos, Position toPos);
    void moveUnit(unitPtr_t unit, Position to); //TODO
    void captureUnit(unitPtr_t unit);
    void uncaptureUnit(unitPtr_t unit, Position pos_old);
    Position findUnitPosition(unitPtr_t unit);
    std::vector<Position> getAvailableCellsForUnit(Position from);
    std::vector<Position> getPositionsOfPlayersTurn(bool isWhitesTurn);

  private:
    void setUnitTo_(unitPtr_t unit, Position pos);

    std::vector<Position> getAvailableDiagonalPositions_(Position from);
    std::vector<Position> getAvailableRowPositions_(Position from);
    std::vector<Position> getAvailableColPositions_(Position from);
    std::vector<Position> getFirstAvailableFromAllDirs_(Position from);
    std::vector<Position> getAvailableKnightPositions_(Position from);
    std::vector<Position> getAvailablePawnPositions_(Position from);

    bool positionIsAvailable_(std::vector<Position> positions, Position pos);
    std::vector<Position>  validatePossiblyAvailablePositions_(std::vector<Position> possible, unitPtr_t forUnit);

    unitVector_t capturedUnits_; // ?

    unitBoardArray_t board_;

    std::vector<Position> lastAvailableMovesCache_;

    unitPtr_t cachedUnit_;
};