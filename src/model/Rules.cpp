#include "Rules.h"

bool Rules::checkMoveValidity(unitType_t unitType, Position fromPos, Position toPos) {
    if(unitType == PAWN) {
        if(toPos.row() == fromPos.row() + 1) return true;
        return false;
    }


    //TODO
    return false;
}