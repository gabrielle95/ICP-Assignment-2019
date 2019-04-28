#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "../common/Position.h"
#include "../common/Color.h"

#ifdef DEBUG
#define STRINGIFY(name) #name
#endif

/*enum color_t {
    BLACK,
    WHITE
};*/

enum unitType_t
{
    KING,   // KING - kral K
    QUEEN,  // QUEEN - dama D
    ROOK,   // ROOK - vez V
    BISHOP, // BISHOP - strelec S
    KNIGHT, // KNIGHT - jezdec J
    PAWN,   // PAWN - pesak p
};

using unitPtr_t = std::shared_ptr<class Unit>;
using unitVector_t = std::vector<unitPtr_t>;

class Unit
{
  public:
    Unit(color_t color, unitType_t type, Position starting_pos)
        : color_(color), type_(type), starting_pos_(starting_pos), hasMovedFromStartingPos_(false), isInCheck_(false)
    {
    }

    virtual color_t color() const
    {
        return this->color_;
    }

    virtual unitType_t type() const
    {
        return this->type_;
    }

    virtual void print() const
    {

        switch (type_)
        {
        case KING:
            std::cout << "KING ";
            break;
        case QUEEN:
            std::cout << "QUEEN ";
            break;
        case ROOK:
            std::cout << "ROOK ";
            break;
        case BISHOP:
            std::cout << "BISHOP ";
            break;
        case KNIGHT:
            std::cout << "KNIGHT ";
            break;
        default:
            std::cout << "PAWN ";
            break;
        }
    }

    virtual bool movedFromStartingPos() const
    {
        return hasMovedFromStartingPos_;
    }

    virtual void setMovedFromStartingPos(bool value = true)
    {
        hasMovedFromStartingPos_ = value;
    }

    virtual Position startingPos() const
    {
        return starting_pos_;
    }

    virtual void setInCheck(bool value)
    {
        isInCheck_ = value;
    }

    virtual bool isInCheck() const
    {
        return isInCheck_;
    }

    virtual void resetFlags()
    {
        hasMovedFromStartingPos_ = false;
        isInCheck_ = false;
    }

  protected:
    color_t color_;
    unitType_t type_;
    Position starting_pos_;
    bool hasMovedFromStartingPos_;
    bool isInCheck_;
};
