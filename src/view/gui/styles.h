#ifndef STYLES_H
#define STYLES_H

#include "../../common/Color.h"

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
};

#endif // STYLES_H
