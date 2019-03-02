#include "SaveFile.h"
#include "../common/ChessException.h"

SaveFile::SaveFile(std::string sFPath) {
    //TODO
}

unitType_t SaveFile::unitTypeFrom_(char c) {
    switch (c)
    {
        case 'K': return unitType_t::KING;
        case 'D': return unitType_t::QUEEN;
        case 'V': return unitType_t::ROOK;
        case 'S': return unitType_t::BISHOP;
        case 'J': return unitType_t::KNIGHT;
        case 'p': return unitType_t::PAWN;
        default:
            throw ChessException("Unknown Unit Type " + std::string(&c));
    }
}

char SaveFile::charFrom_(unitType_t unitType) {
    switch (unitType)
    {
        case unitType_t::KING: return 'K';
        case unitType_t::QUEEN: return 'D';
        case unitType_t::ROOK: return 'V';
        case unitType_t::BISHOP: return 'S';
        case unitType_t::KNIGHT: return 'J';
        case unitType_t::PAWN: return 'p';
        default:
            throw ChessException("Unit Type supplied not part of enum.");
            //foolproof
    }
}