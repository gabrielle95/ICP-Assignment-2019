/*
 * @file Rules.h
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

#include <cstdlib>
#include "./Unit.h"
#include "../common/Position.h"

class Rules
{
  public:

    /**
     * @brief Checks the validity of a given move
     *
     * @param unit The unit that moves
     * @param fromPos The unit position
     * @param toPos The position to which it moves
     * @return true The move is valid
     * @return false The move is not valid
     */
    static bool checkMoveValidity(unitPtr_t unit, Position fromPos, Position toPos);

    /**
     * @brief Get the cell distance between two positions
     *
     * @param one The first position
     * @param two The second position
     * @return int The cell distance
     */
    static int getDistance(Position one, Position two);

    /**
     * @brief Get the row distance of two positions
     *
     * @param one The first position
     * @param two The second position
     * @return int The distance of the rows in the positions
     */
    static int getRowDistance(Position one, Position two);

    /**
     * @brief Get the column distance of two positions
     *
     * @param one The first position
     * @param two The second position
     * @return int The distance of the columns in the positons
     */
    static int getColDistance(Position one, Position two);

    /**
     * @brief Validate the pawn movement
     *
     * @param color The pawns color
     * @param fromPos The position from which it moves
     * @param toPos The position to which it moves
     * @param movedFromStartingPos Whether it already moved from default position
     * @return true The pawn can move
     * @return false The pawn cannot move
     */
    static bool checkPawnMoving(color_t color, Position fromPos, Position toPos, bool movedFromStartingPos);

    /**
     * @brief Check if the pawn can perform capture
     *
     * @param color The color of the pawn
     * @param fromPos The position from which the pawn wants to perform capture
     * @param toPos The position to which the pawn moves on capture
     * @return true The pawn can capture
     * @return false The pawn cannot capture
     */
    static bool checkPawnCapturing(color_t color, Position fromPos, Position toPos);

  private:
    static bool checkRook_(Position fromPos, Position toPos);
    static bool checkBishop_(Position fromPos, Position toPos);
    static bool checkKnight_(Position fromPos, Position toPos);
    static bool checkKing_(Position fromPos, Position toPos);
    static bool checkQueen_(Position fromPos, Position toPos);
};