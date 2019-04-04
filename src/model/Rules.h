#pragma once

#include <cstdlib>
#include "./Unit.h"
#include "../common/Position.h"

class Rules
{
  public:
    static bool checkMoveValidity(unitPtr_t unit, Position fromPos, Position toPos);
    static std::vector<Position> getValidMoves(unitPtr_t unit);
    static int getDistance(Position one, Position two);
    static int getRowDistance(Position one, Position two);
    static int getColDistance(Position one, Position two);

  private:
    static bool checkPawn_(color_t color, Position fromPos, Position toPos, bool movedFromStartingPos);
    static bool checkRook_(Position fromPos, Position toPos);
    static bool checkBishop_(Position fromPos, Position toPos);
    static bool checkKnight_(Position fromPos, Position toPos);
    static bool checkKing_(Position fromPos, Position toPos);
    static bool checkQueen_(Position fromPos, Position toPos);
};