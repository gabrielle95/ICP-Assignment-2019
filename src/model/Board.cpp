#include "../common/Color.h"
#include "Board.h"

Board::Board() {

    /******** WHITE ********/

    board_.at(A).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(A, TWO));
    board_.at(B).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(B, TWO));
    board_.at(C).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(C, TWO));
    board_.at(D).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(D, TWO));
    board_.at(E).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(E, TWO));
    board_.at(F).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(F, TWO));
    board_.at(G).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(G, TWO));
    board_.at(H).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(H, TWO));

    board_.at(A).at(ONE) = std::make_shared<Unit>(WHITE, ROOK, Position(A, ONE));
    board_.at(H).at(ONE) = std::make_shared<Unit>(WHITE, ROOK, Position(H, ONE));

    board_.at(B).at(ONE) = std::make_shared<Unit>(WHITE, KNIGHT, Position(B, ONE));
    board_.at(G).at(ONE) = std::make_shared<Unit>(WHITE, KNIGHT, Position(G, ONE));

    board_.at(C).at(ONE) = std::make_shared<Unit>(WHITE, BISHOP, Position(C, ONE));
    board_.at(F).at(ONE) = std::make_shared<Unit>(WHITE, BISHOP, Position(F, ONE));

    board_.at(D).at(ONE) = std::make_shared<Unit>(WHITE, QUEEN, Position(D, ONE));
    board_.at(E).at(ONE) = std::make_shared<Unit>(WHITE, KING, Position(E, ONE));

        /******** BLACK ********/

    board_.at(A).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(A, SEVEN));
    board_.at(B).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(B, SEVEN));
    board_.at(C).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(C, SEVEN));
    board_.at(D).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(D, SEVEN));
    board_.at(E).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(E, SEVEN));
    board_.at(F).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(F, SEVEN));
    board_.at(G).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(G, SEVEN));
    board_.at(H).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(H, SEVEN));

    board_.at(A).at(EIGHT) = std::make_shared<Unit>(BLACK, ROOK, Position(A, EIGHT));
    board_.at(H).at(EIGHT) = std::make_shared<Unit>(BLACK, ROOK, Position(H, EIGHT));

    board_.at(B).at(EIGHT) = std::make_shared<Unit>(BLACK, KNIGHT, Position(B, EIGHT));
    board_.at(G).at(EIGHT) = std::make_shared<Unit>(BLACK, KNIGHT, Position(G, EIGHT));

    board_.at(C).at(EIGHT) = std::make_shared<Unit>(BLACK, BISHOP, Position(C, EIGHT));
    board_.at(F).at(EIGHT) = std::make_shared<Unit>(BLACK, BISHOP, Position(F, EIGHT));

    board_.at(D).at(EIGHT) = std::make_shared<Unit>(BLACK, QUEEN, Position(D, EIGHT));
    board_.at(E).at(EIGHT) = std::make_shared<Unit>(BLACK, KING, Position(E, EIGHT));

}

unitPtr_t Board::At(letter_t clm, rowPos_t row) {

    try {
        return board_.at(clm).at(row);
    }
    catch(std::out_of_range &e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Error: Accessed out of range coords.\n";
    }

}

unitPtr_t Board::At(Position pos) {
    return At(pos.clm(), pos.row());
}

void Board::print() {
    for(int c = A; c < board_.size(); c++) {

        for(int r = ONE; r < board_.at(c).size(); r++) {
            if(board_.at(c).at(r)) board_.at(c).at(r)->print();
        }
    }
}

bool Board::checkMoveValidity(unitPtr_t unit, Position fromPos, Position toPos) {

    bool posAvailable = true;

    /* REFACTOR THIS PART */
    if(unit->type() == ROOK) {
        posAvailable = positionIsAvailable_(getAvailableRowPositions_(fromPos),toPos)
                        || positionIsAvailable_(getAvailableColPositions_(fromPos),toPos);
    }
    else if(unit->type() == BISHOP) {
        posAvailable = positionIsAvailable_(getAvailableDiagonalPositions_(fromPos),toPos);
    }
    else if(unit->type() == KING || unit->type() == QUEEN) {
        posAvailable = positionIsAvailable_(getAvailableRowPositions_(fromPos),toPos)
                        || positionIsAvailable_(getAvailableColPositions_(fromPos),toPos)
                        || positionIsAvailable_(getAvailableDiagonalPositions_(fromPos),toPos);
    }
    else if(unit->type() == PAWN) {
        posAvailable = positionIsAvailable_(getAvailableRowPositions_(fromPos),toPos);
    }

    return Rules::checkMoveValidity(unit, fromPos, toPos) && posAvailable;
}

void Board::moveUnit(unitPtr_t unit, Position to) {
    Position unitPos = findUnitPosition(unit);

    // unit is not captured
    if(unitPos.isValid()) {
        if(At(to) != nullptr) {
            captureUnit(At(to));
        }
        setUnitTo_(unit, to);
        setUnitTo_(nullptr, unitPos);
        if(!unit->movedFromStartingPos()) unit->setMovedFromStartingPos();
    }
}

void Board::captureUnit(unitPtr_t unit) {
    capturedUnits_.emplace_back(unit);
}

Position Board::findUnitPosition(unitPtr_t unit) {
    for(int c = A; c < board_.size(); c++) {

        for(int r = ONE; r < board_.at(c).size(); r++) {
            if(board_.at(c).at(r) == unit) {
                return Position((letter_t)c, (rowPos_t)r);
            }
        }
    }
    return Position((letter_t)-1, (rowPos_t)-1);
}

std::vector<Position> Board::getAvailableCellsForUnit(Position from) {
    unitPtr_t unit = At(from);
    if(unit != nullptr) {
        std::vector<Position> rows;
        std::vector<Position> cols;
        std::vector<Position> diagonals;

        if(unit->type() == ROOK) {
            rows = getAvailableRowPositions_(from);
            cols = getAvailableColPositions_(from);
            std::move(rows.begin(), rows.end(), lastAvailableMovesCache_.end());
            std::move(cols.begin(), cols.end(), lastAvailableMovesCache_.end());
        }
        else if(unit->type() == BISHOP) {
            diagonals = getAvailableDiagonalPositions_(from);
            std::move(diagonals.begin(), diagonals.end(), lastAvailableMovesCache_.end());
        }
        else if(unit->type() == QUEEN) {
            rows = getAvailableRowPositions_(from);
            cols = getAvailableColPositions_(from);
            diagonals = getAvailableDiagonalPositions_(from);
            std::move(rows.begin(), rows.end(), lastAvailableMovesCache_.end());
            std::move(cols.begin(), cols.end(), lastAvailableMovesCache_.end());
            std::move(diagonals.begin(), diagonals.end(), lastAvailableMovesCache_.end());
        }
        //TODO
    }
    return lastAvailableMovesCache_;
}


void Board::setUnitTo_(unitPtr_t unit, Position pos) {
    board_.at(pos.clm()).at(pos.row()) = unit;
}

std::vector<Position> Board::getAvailableDiagonalPositions_(Position from) {

    std::vector<Position> available;

    int col, row;

    for(col = from.clm()-1, row = from.row()+1; col >= COL_MIN, row <= ROW_MAX; col--, row++) {
        if(col < COL_MIN) break;
        if(board_.at(col).at(row) == nullptr) {
            available.push_back(Position((letter_t)col, (rowPos_t)row));
            continue;
        }
        break;
    }
    for(col = from.clm()+1, row = from.row()+1; col <= COL_MAX, row <= ROW_MAX; col++, row++) {
        if(col > COL_MAX) break;
        if(board_.at(col).at(row) == nullptr) {
            available.push_back(Position((letter_t)col, (rowPos_t)row));
            continue;
        }
        break;
    }
    for(col = from.clm()-1, row = from.row()-1; col >= COL_MIN, row >= ROW_MIN; col--, row--) {
        if(col < COL_MIN) break;
        if(board_.at(col).at(row) == nullptr) {
            available.push_back(Position((letter_t)col, (rowPos_t)row));
            continue;
        }
        break;
    }
    for(col = from.clm()+1, row = from.row()-1; col <= COL_MAX, row >= ROW_MIN; col++, row--) {
        if(col > COL_MAX) break;
        if(board_.at(col).at(row) == nullptr) {
            available.push_back(Position((letter_t)col, (rowPos_t)row));
            continue;
        }
        break;
    }
    return available;
}

std::vector<Position> Board::getAvailableRowPositions_(Position from) {
    int row;
    std::vector<Position> available;

    for(row = from.row()-1; row >= ROW_MIN; row--) {
        if(board_.at(from.clm()).at(row) == nullptr) {
            available.push_back(Position(from.clm(), (rowPos_t)row));
            continue;
        }
        break;
    }
    for(row = from.row()+1; row <= ROW_MAX; row++) {
        if(board_.at(from.clm()).at(row) == nullptr) {
            available.push_back(Position(from.clm(), (rowPos_t)row));
            continue;
        }
        break;
    }
    return available;
}

std::vector<Position> Board::getAvailableColPositions_(Position from) {
    int col;
    std::vector<Position> available;

    for(col = from.clm()-1; col >= COL_MIN; col--) {
        if(board_.at(col).at(from.row()) == nullptr) {
            available.push_back(Position((letter_t)col, from.row()));
            continue;
        }
        break;
    }
    for(col = from.clm()+1; col <= ROW_MAX; col++) {
        if(board_.at(col).at(from.row()) == nullptr) {
            available.push_back(Position((letter_t)col, from.row()));
            continue;
        }
        break;
    }
    return available;
}

bool Board::positionIsAvailable_(std::vector<Position> positions, Position pos) {
    for (auto& p : positions) {
        if(p == pos) return true;
    };
    return false;
}
