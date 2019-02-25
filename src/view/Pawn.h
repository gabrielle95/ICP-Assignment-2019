#pragma once

#include "Unit.h"

class Pawn : public Unit {
    public:
        Pawn(Color color, int xStart, int yStart);
        virtual void moveTo(int x, int y);

    private:

        virtual bool _canMoveTo(int x, int y);

        // determines if the pawn has gone through first step
        // first step, pawn can move 2 fields instead of 1
        bool hasMovedFromOriginalPos_ = false;
};