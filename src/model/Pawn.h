#pragma once

#include "Unit.h"

class Pawn : public Unit {
    public:
        Pawn(Color color, int xStart, int yStart) {
            color_ = color;
            x_ = xStart;
            y_ = yStart;
        }

        virtual void moveTo(int x, int y) {
            x_ = x;
            y_ = y;
        }

        #ifdef DEBUG
        virtual void print () {
            std::cout << "This is a " << color_ << " Pawn with pos: " << x_ << "  " << y_ << "\n";
        }
        #endif
};