#pragma once

#include <iostream>
#include <memory>
#include "../common/Position.h"

#ifdef DEBUG
#define STRINGIFY( name ) # name
#endif

enum Color_t {
    BLACK,
    WHITE
};

enum unitType_t {
    KING, // KING - kral K
    QUEEN, // QUEEN - dama D
    ROOK, // ROOK - vez V
    BISHOP, // BISHOP - strelec S
    KNIGHT, // KNIGHT - jezdec J
    PAWN, // PAWN - pesak p
};

class Unit {
    public:
        virtual void moveTo(Position pos) = 0;

        virtual int row() const {
            return pos_.row();
        }

        virtual int clm() const {
            return pos_.clm();
        }

        virtual Color_t color() const {
            return this->color_;
        }

        virtual Position getPos() const {
            return this->pos_;
        }

        virtual void print () = 0;


    protected:
        Position pos_;
        Color_t color_;
        unitType_t unitType_;
};

typedef std::shared_ptr<Unit> unitPtr_t;