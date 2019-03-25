#pragma once

#include "./Unit.h"
#include "../common/Position.h"

class Rules {
    public:
        static bool checkMoveValidity(unitType_t unitType, Position fromPos, Position toPos);
        static std::vector<Position> getValidMoves(unitPtr_t unit);
};