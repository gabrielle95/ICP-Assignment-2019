#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "../common/Position.h"

#ifdef DEBUG
#define STRINGIFY( name ) # name
#endif

enum color_t {
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

using pseudoUnitPtr_t = std::shared_ptr<struct PseudoUnit>;
using unitPtr_t = std::shared_ptr<class Unit>;
using unitVector_t = std::vector<unitPtr_t>;

class PseudoUnit {
    Position pos;
    color_t color;
    unitType_t type;
};

class Unit {
    public:

        Unit(color_t color, unitType_t type, Position starting_pos)
        : color_(color), type_(type), pos_(starting_pos)
        {}

        virtual void moveTo(Position pos) {
            pos_ = pos;
        }

        virtual int row() const {
            return pos_.row();
        }

        virtual int clm() const {
            return pos_.clm();
        }

        virtual color_t color() const {
            return this->color_;
        }

        virtual Position getPos() const {
            return this->pos_;
        }

        virtual unitType_t type() const {
            return this->type_;
        }

    protected:
        Position pos_;
        color_t color_;
        unitType_t type_;
};