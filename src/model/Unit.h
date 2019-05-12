/*
 * @file Unit.h
 *
 * Project name:
 * Chess 2019
 *
 * Description:
 * http://www.fit.vutbr.cz/study/courses/ICP/public/ICP-PRJ-zadani.html.cs
 *
 * Team:
 * @author Gabriela Pacakova (xpacak01)
 * @author Adam Lanicek (xlanic04)
 */

#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "../common/Position.h"
#include "../common/Color.h"

#ifdef DEBUG
#define STRINGIFY(name) #name
#endif

/**
 * @brief Enum describing all the unit types on the board
 *
 */
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

/**
 * @brief Class implementing a chess unit on the board
 *
 */
class Unit
{
  public:
    /**
   * @brief Construct a new Unit object
   *
   * @param color Color of the unit
   * @param type Type of the unit
   * @param starting_pos Unit's starting position on the board
   */
    Unit(color_t color, unitType_t type, Position starting_pos)
        : color_(color), type_(type), starting_pos_(starting_pos), hasMovedFromStartingPos_(false)
    {
    }

    /**
     * @brief Getter for the unit color
     *
     * @return color_t Unit color
     */
    color_t color() const
    {
        return this->color_;
    }

    /**
     * @brief Getter for the unit type
     *
     * @return unitType_t Unit type
     */
    unitType_t type() const
    {
        return this->type_;
    }

    /**
     * @brief Getter for a flag indication if the unit has moved from its starting position
     *
     * @return true The unit has moved from starting position
     * @return false The unit has not moved from starting position
     */
    bool movedFromStartingPos() const
    {
        return hasMovedFromStartingPos_;
    }

    /**
     * @brief Setter for the flag if the unit moved from the starting position
     *
     * @param value The value of the flag
     */
    void setMovedFromStartingPos(bool value = true)
    {
        hasMovedFromStartingPos_ = value;
    }

    /**
     * @brief Getter for the starting position
     *
     * @return Position The starting position of the unit
     */
    Position startingPos() const
    {
        return starting_pos_;
    }

    /**
     * @brief Resets all the unit flags to their default values
     *
     */
    void resetFlags()
    {
        hasMovedFromStartingPos_ = false;
    }

  protected:
    color_t color_;
    unitType_t type_;
    Position starting_pos_;
    bool hasMovedFromStartingPos_;
};
