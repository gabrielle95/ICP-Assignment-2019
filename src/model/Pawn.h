#pragma once

#include "Unit.h"

class Pawn : public Unit {
    public:
        Pawn(Color_t color, Position starting_pos) {
            color_ = color;
            pos_ = starting_pos;
            unitType_ = PAWN;
        }

        virtual void moveTo(Position pos) {
            pos_ = pos;
        }

        virtual void print () {
            #ifdef DEBUG
            std::cout << "This is a " << color_ << " Pawn with pos: " << pos_.clm() << "  " << pos_.row() << "\n";
            #endif
        }

};