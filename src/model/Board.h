/*
 * @file Board.h
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

#include <memory>
#include <algorithm>
#include "Unit.h"
#include "Rules.h"

const int BOARD_LENGTH = 8;
const int UNIT_CAPACITY = 32;
const int COL_MIN = 0;
const int COL_MAX = 7;
const int ROW_MIN = COL_MIN;
const int ROW_MAX = COL_MAX;

using unitBoardArray_t = std::array<std::array<unitPtr_t, BOARD_LENGTH>, BOARD_LENGTH>;

using boardPtr_t = std::shared_ptr<class Board>;

/**
 * @brief The class defining the game board
 *
 */
class Board
{

public:

  /**
   * @brief Construct a new Board object
   *
   */
  Board();

  /**
   * @brief Gets the unit at the certain position
   *
   * @param clm The column of the position
   * @param row The for of the position
   * @return unitPtr_t The unit that is at the given position or nullptr
   */
  unitPtr_t At(letter_t clm, rowPos_t row);

  /**
   * @brief Gets the unit at a certain position
   *
   * @param pos The position of the desired unit
   * @return unitPtr_t The unitthat is at given position or nullptr
   */
  unitPtr_t At(Position pos);

  /**
   * @brief Checks a validity of a given move
   *
   * @param unit The unit that wants to perform the move
   * @param fromPos The current position of this unit
   * @param toPos The position the unit wants to move to
   * @return true The move is valid
   * @return false The move is not valid
   */
  bool checkMoveValidity(unitPtr_t unit, Position fromPos, Position toPos);

  /**
   * @brief Move the unit setting its position
   *
   * @param unit The unit to move
   * @param to The position where to move it
   */
  void moveUnit(unitPtr_t unit, Position to);

  /**
   * @brief Capture the unit, inserting it into captured units container
   *
   * @param unit The unit being captured
   */
  void captureUnit(unitPtr_t unit);

  /**
   * @brief Uncapture the unit (used with undo)
   *
   * @param unit The unit to uncapture
   * @param pos_old The position of the unit before the capture
   */
  void uncaptureUnit(unitPtr_t unit, Position pos_old);

  /**
   * @brief Finds the position of a given unit on the board
   *
   * @param unit The unit whose position we want
   * @return Position The position found
   */
  Position findUnitPosition(unitPtr_t unit);

  /**
   * @brief Get the Available positions For Unit on a certain position
   *
   * @param from The units position
   * @return std::vector<Position> The available positions for this unit to move to
   */
  std::vector<Position> getAvailableCellsForUnit(Position from);

  /**
   * @brief Get the positions of units of a certain team (color)
   *
   * @param isWhitesTurn Its whites turn to go
   * @return std::vector<Position> The found positions
   */
  std::vector<Position> getPositionsOfPlayersTurn(bool isWhitesTurn);

  /**
   * @brief Find the units position when deserializing short notation
   *
   * @param unitType The type of the unit
   * @param color The color of the unit
   * @param to The position it is moving to
   * @param hintingRow The row that hints in case there are multiple choices
   * @param hintingColumn A column that hints in case there are multiple choices
   * @return unitPtr_t The found unit
   */
  unitPtr_t findActualUnitForShortNotation(unitType_t unitType, color_t color, Position to, int hintingRow = -1, int hintingColumn = -1);

  /**
   * @brief Reset the board putting units to their starting positions and resetting its flag
   *
   */
  void resetBoard();

  /**
   * @brief Resets the king in check flag
   *
   */
  void resetCheck();

  /**
   * @brief Finds out if the desired teams king is in check
   *
   * @param color Color of the king
   * @return true King is in check
   * @return false King is not in check
   */
  bool isKingInCheck(color_t color);

  /**
   * @brief Finds out if the desired players king is stalemated
   *
   * @param color The color of the king
   * @return true The king got stalemated
   * @return false The king is not stalemated
   */
  bool isKingStalemated(color_t color);

  /**
   * @brief Finds whether a desired king got checkmated
   *
   * @param color The color of the king
   * @return true The king got checkmated
   * @return false The king is not checkmated
   */
  bool isKingCheckMated(color_t color);

private:
  std::vector<Position> getAvailablePositionsForOpposingTeam_(color_t color);
  void setUnitTo_(unitPtr_t unit, Position pos);
  std::vector<Position> getAvailableDiagonalPositions_(Position from);
  std::vector<Position> getAvailableRowPositions_(Position from);
  std::vector<Position> getAvailableColPositions_(Position from);
  std::vector<Position> getFirstAvailableFromAllDirs_(Position from);
  std::vector<Position> getAvailableKnightPositions_(Position from);
  std::vector<Position> getAvailablePawnPositions_(Position from);

  bool positionIsAvailable_(std::vector<Position> positions, Position pos);
  std::vector<Position> validatePossiblyAvailablePositions_(std::vector<Position> possible, unitPtr_t forUnit);
  std::vector<Position> intersectPositionVectors_(std::vector<Position> a, std::vector<Position> b);

  void initBoard_();

  unitVector_t capturedUnits_;

  unitBoardArray_t board_;

  unitVector_t allUnits_;

  std::vector<Position> lastAvailableMovesCache_;

  unitPtr_t cachedUnit_;
};