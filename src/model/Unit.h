#pragma once

#include <iostream>
#include <memory>

#ifdef DEBUG
#define STRINGIFY( name ) # name
#endif

class Unit;
typedef std::shared_ptr<Unit> unitPtr_t;

enum Color {
    White = 0,
    Black = 1
};

class Unit {
    public:
        virtual void moveTo(int x, int y) = 0;

        virtual int x() const {
            return this->x_;
        }

        virtual int y() const {
            return this->y_;
        }

        virtual Color color() const {
            return this->color_;
        }

        #ifdef DEBUG
        virtual void print () = 0;
        #endif

    protected:
        int x_, y_;
        Color color_;
};