#ifndef STYLES_H
#define STYLES_H

#include "../../common/Color.h"
#include "../../model/Unit.h"

class Styles
{
  public:
    inline static QString cellSelectedBg = "background-color: rgb(255, 0, 0);";
    inline static QString cellAllowedMoveBg = "background-color: rgb(0, 255, 0);";

    inline static QString cellRookWhiteFg = "border-image: url(:/res/chess_icons/rook_white.svg);";
    inline static QString cellRookBlackFg = "border-image: url(:/res/chess_icons/rook_black.svg);";

    inline static QString cellBishopWhiteFg = "border-image: url(:/res/chess_icons/bishop_white.svg);";
    inline static QString cellBishopBlackFg = "border-image: url(:/res/chess_icons/bishop_black.svg);";

    inline static QString cellKnightWhiteFg = "border-image: url(:/res/chess_icons/knight_white.svg);";
    inline static QString cellKnightBlackFg = "border-image: url(:/res/chess_icons/knight_black.svg);";

    inline static QString cellKingWhiteFg = "border-image: url(:/res/chess_icons/king_white.svg);";
    inline static QString cellKingBlackFg = "border-image: url(:/res/chess_icons/king_black.svg);";

    inline static QString cellQueenWhiteFg = "border-image: url(:/res/chess_icons/queen_white.svg);";
    inline static QString cellQueenBlackFg = "border-image: url(:/res/chess_icons/queen_black.svg);";

    inline static QString cellPawnWhiteFg = "border-image: url(:/res/chess_icons/pawn_white.svg);";
    inline static QString cellPawnBlackFg = "border-image: url(:/res/chess_icons/pawn_black.svg);";

    inline static QString openIcon = "border-image: url(:/res/app_icons/open.png);";
    inline static QString saveIcon = "border-image: url(:/res/app_icons/save.png);";
    inline static QString undoIcon = "border-image: url(:/res/app_icons/undo.png);";
    inline static QString redoIcon = "border-image: url(:/res/app_icons/redo.png);";
    inline static QString forwardIcon = "border-image: url(:/res/app_icons/forward.png);";
    inline static QString backwardIcon = "border-image: url(:/res/app_icons/backward.png);";

    inline static QString greyBackground = "background-color: rgb(136, 138, 133);";

    inline static QString margin10px = "margin: 10px;";

    inline static QString getStyleFrom(unitType_t type, color_t color) {
        if(color == BLACK) {
            if(type == PAWN) return cellPawnBlackFg;
            if(type == ROOK) return cellRookBlackFg;
            if(type == BISHOP) return cellBishopBlackFg;
            if(type == KNIGHT) return cellKnightBlackFg;
            if(type == KING) return cellKingBlackFg;
            if (type == QUEEN) return cellQueenBlackFg;
        }
        else if(color == WHITE) {
            if(type == PAWN) return cellPawnWhiteFg;
            if(type == ROOK) return cellRookWhiteFg;
            if(type == BISHOP) return cellBishopWhiteFg;
            if(type == KNIGHT) return cellKnightWhiteFg;
            if(type == KING) return cellKingWhiteFg;
            if (type == QUEEN) return cellQueenWhiteFg;
        }
    }
};

#endif // STYLES_H
