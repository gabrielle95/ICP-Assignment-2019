#pragma once

#include <iostream>
#include <memory>
#include "../common/Position.h"

#ifdef DEBUG
#define STRINGIFY( name ) # name
#endif

class Unit;
typedef std::shared_ptr<Unit> unitPtr_t;

enum Color_t {
    black,
    white
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
};