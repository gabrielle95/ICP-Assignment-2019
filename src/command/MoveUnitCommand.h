/*
 * @file MoveUnitCommand.h
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

#include "../model/Board.h"
#include "../model/Unit.h"
#include "ICommand.h"

/**
 * @brief A command that moves the unit in game and sets all appropriate flags.
 *
 */
class MoveUnitCommand : public ICommand
{
public:
  /**
   * @brief Construct a new Move Unit Command object
   *
   * @param board The board on which the command is performed
   * @param unit The unit on which the command is performed
   * @param pos The new position for the unit to move to
   */
  MoveUnitCommand(boardPtr_t board, unitPtr_t unit, Position pos)
      : board_(board),
        unit_(unit),
        pos_(pos),
        isCapturer_(false),
        checked_(false),
        checkMate_(false)
  {
  }

  /**
   * @brief Gets the unit's old position
   *
   * @return Position The Position of the unit before the move
   */
  virtual Position old_pos() const
  {
    return pos_old_;
  }

  /**
   * @brief Gets the units new position
   *
   * @return Position The position of the unit after move
   */
  virtual Position new_pos() const
  {
    return pos_;
  }

  /**
   * @brief Gets the unit that the commanded unit captured
   *
   * @return unitPtr_t The unit captured by the commanded unit
   */
  virtual unitPtr_t capturedUnit() const
  {
    return capturedUnit_;
  }

  /**
   * @brief Gets the unit the command is performed on
   *
   * @return unitPtr_t The unit that is moving
   */
  virtual unitPtr_t movingUnit() const
  {
    return unit_;
  }

  /**
   * @brief Gets whether the moving unit has checked an enemy king
   *
   * @return true The unit has checked the enemy king
   * @return false The unit has not checked the enemy king
   */
  virtual bool checked() const
  {
    return checked_;
  }

  /**
   * @brief Gets whether the moving unit has checkmated the enemy king
   *
   * @return true The unit has checkmated the enemy king
   * @return false The unit has not checkmated the enemy king
   */
  virtual bool mated() const
  {
    return checkMate_;
  }

private:
  virtual void execute()
  {
    pos_old_ = board_->findUnitPosition(unit_);

    capturedUnit_ = board_->At(pos_);

    if (capturedUnit_ != nullptr)
    {
      board_->captureUnit(capturedUnit_);
      isCapturer_ = true;

      //workaround
      if(capturedUnit_->type() == KING)
        checkMate_ = true;

    }
    board_->moveUnit(unit_, pos_);

    if(/*board_->isKingCheckMated(WHITE) || board_->isKingCheckMated(BLACK)*/board_->isGameFinished())
    {
      checkMate_ = true;
    }
    else if(board_->isKingInCheck(WHITE) || board_->isKingInCheck(BLACK))
    {
      checked_ = true;
    }

  }

  virtual void undo()
  {
    board_->moveUnit(unit_, pos_old_);
    if (capturedUnit_ != nullptr)
      board_->moveUnit(capturedUnit_, pos_);
  }

  virtual void redo()
  {
    if (capturedUnit_ != nullptr)
      board_->captureUnit(capturedUnit_);

    board_->moveUnit(unit_, pos_);
  }

  boardPtr_t board_;
  unitPtr_t unit_;
  Position pos_;
  Position pos_old_;

  bool isCapturer_;
  unitPtr_t capturedUnit_;

  bool checked_;
  bool checkMate_;
};
