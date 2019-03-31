#include "Rules.h"

bool Rules::checkMoveValidity(unitPtr_t unit, Position fromPos, Position toPos) {

    switch (unit->type())
    {
        case PAWN:
            return Rules::checkPawn_(unit->color(), fromPos, toPos, unit->movedFromStartingPos());
        case ROOK:
            return Rules::checkRook_(fromPos, toPos);
        case BISHOP:
            return Rules::checkBishop_(fromPos, toPos);
        case KNIGHT:
            return Rules::checkKnight_(fromPos, toPos);
        case KING:
            return checkKing_(fromPos, toPos);
        case QUEEN:
            return checkQueen_(fromPos, toPos);
        default:
            return false;
    }
}

int Rules::getDistance(Position one, Position two) {
    return abs(one.clm() - two.clm()) + abs(one.row() - two.row());
}

int Rules::getRowDistance(Position one, Position two) {
    return abs(one.row() - two.row());
}

int Rules::getColDistance(Position one, Position two) {
    return abs(one.clm() - two.clm());
}

bool Rules::checkPawn_(color_t color, Position fromPos, Position toPos, bool movedFromStartingPos) {

    // think about how to do capturing
    if(fromPos.clm() != toPos.clm()) return false;

    const int defaultStep = 1;
    int maxStep = (movedFromStartingPos ? 1 : 2);


    if(color == BLACK && toPos.row() > fromPos.row()) return false;
    if(color == WHITE && toPos.row() < fromPos.row()) return false;

    return getRowDistance(fromPos, toPos) - maxStep == 0 || getRowDistance(fromPos, toPos) - defaultStep == 0;
}

bool Rules::checkRook_(Position fromPos, Position toPos) {

    int columnDst = getColDistance(fromPos, toPos);
    int rowDst = getRowDistance(fromPos, toPos);

    return (columnDst != 0 && rowDst == 0) || (columnDst == 0 && rowDst != 0);
}

bool Rules::checkBishop_(Position fromPos, Position toPos) {
    return getColDistance(fromPos, toPos) == getRowDistance(fromPos, toPos);
}

bool Rules::checkKnight_(Position fromPos, Position toPos) {
    return fromPos.row() != toPos.row() && fromPos.clm() != toPos.clm() && getDistance(fromPos, toPos) == 3;
}

bool Rules::checkKing_(Position fromPos, Position toPos) {

    int columnDst = getColDistance(fromPos, toPos);
    int rowDst = getRowDistance(fromPos, toPos);

    return (rowDst == 1 && columnDst == 1)
            || (rowDst == 1 && columnDst == 0)
            || (rowDst == 0 && columnDst == 1);
}

bool Rules::checkQueen_(Position fromPos, Position toPos) {
    return Rules::checkRook_(fromPos, toPos) ||  Rules::checkBishop_(fromPos, toPos);
}