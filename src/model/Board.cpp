#include "Board.h"

Board::Board() {



    playingUnits_ = {

        /******** WHITE ********/

        std::make_shared<Unit>(WHITE, PAWN, Position(A, TWO)),
        std::make_shared<Unit>(WHITE, PAWN, Position(B, TWO)),
        std::make_shared<Unit>(WHITE, PAWN, Position(C, TWO)),
        std::make_shared<Unit>(WHITE, PAWN, Position(D, TWO)),
        std::make_shared<Unit>(WHITE, PAWN, Position(E, TWO)),
        std::make_shared<Unit>(WHITE, PAWN, Position(F, TWO)),
        std::make_shared<Unit>(WHITE, PAWN, Position(G, TWO)),
        std::make_shared<Unit>(WHITE, PAWN, Position(H, TWO)),

        std::make_shared<Unit>(WHITE, ROOK, Position(A, ONE)),
        std::make_shared<Unit>(WHITE, ROOK, Position(H, ONE)),

        std::make_shared<Unit>(WHITE, KNIGHT, Position(B, ONE)),
        std::make_shared<Unit>(WHITE, KNIGHT, Position(G, ONE)),

        std::make_shared<Unit>(WHITE, BISHOP, Position(C, ONE)),
        std::make_shared<Unit>(WHITE, BISHOP, Position(F, ONE)),

        std::make_shared<Unit>(WHITE, QUEEN, Position(D, ONE)),
        std::make_shared<Unit>(WHITE, KING, Position(E, ONE)),

        /******** BLACK ********/

        std::make_shared<Unit>(BLACK, PAWN, Position(A, SEVEN)),
        std::make_shared<Unit>(BLACK, PAWN, Position(B, SEVEN)),
        std::make_shared<Unit>(BLACK, PAWN, Position(C, SEVEN)),
        std::make_shared<Unit>(BLACK, PAWN, Position(D, SEVEN)),
        std::make_shared<Unit>(BLACK, PAWN, Position(E, SEVEN)),
        std::make_shared<Unit>(BLACK, PAWN, Position(F, SEVEN)),
        std::make_shared<Unit>(BLACK, PAWN, Position(G, SEVEN)),
        std::make_shared<Unit>(BLACK, PAWN, Position(H, SEVEN)),

        std::make_shared<Unit>(BLACK, ROOK, Position(A, EIGHT)),
        std::make_shared<Unit>(BLACK, ROOK, Position(H, EIGHT)),

        std::make_shared<Unit>(BLACK, KNIGHT, Position(B, EIGHT)),
        std::make_shared<Unit>(BLACK, KNIGHT, Position(G, EIGHT)),

        std::make_shared<Unit>(BLACK, BISHOP, Position(C, EIGHT)),
        std::make_shared<Unit>(BLACK, BISHOP, Position(F, EIGHT)),

        std::make_shared<Unit>(BLACK, QUEEN, Position(D, EIGHT)),
        std::make_shared<Unit>(BLACK, KING, Position(E, EIGHT))
    };

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