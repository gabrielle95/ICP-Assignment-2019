#pragma once

#include "../model/Board.h"
#include "../model/Unit.h"
#include "ICommand.h"

class MoveUnitCommand : public ICommand
{
public:
  MoveUnitCommand(boardPtr_t board, unitPtr_t unit, Position pos)
      : board_(board),
        unit_(unit),
        pos_(pos),
        isCapturer_(false),
        checkedKing_(false),
        staleMatedKing_(false),
        checkMatedKing_(false)
  {
  }

  virtual Position old_pos() const
  {
    return pos_old_;
  }

  virtual Position new_pos() const
  {
    return pos_;
  }

  virtual unitPtr_t capturedUnit() const
  {
    return capturedUnit_;
  }

  virtual unitPtr_t movingUnit() const
  {
    return unit_;
  }

  virtual bool checked() const
  {
    return checkedKing_;
  }

  virtual bool mated() const
  {
    return checkMatedKing_ || staleMatedKing_;
  }

private:
  virtual void execute()
  {
    color_t oppositeColor = unit_->color() == WHITE ? BLACK : WHITE;
    pos_old_ = board_->findUnitPosition(unit_);

    /* if enemy king is in check before making my move */
    /* then i have won, no  matter what move i make */
    checkMatedKing_ = board_->isKingInCheck(oppositeColor);
    staleMatedKing_ = board_->isKingStalemated(oppositeColor);

    capturedUnit_ = board_->At(pos_);

    if (capturedUnit_ != nullptr)
    {
      board_->captureUnit(capturedUnit_);
      isCapturer_ = true;
    }
    board_->moveUnit(unit_, pos_);

    /* has this move made enemy king in check ?*/
    checkedKing_ = board_->isKingInCheck(oppositeColor);


    /* has this move made my king in check(mate) ?*/
    board_->isKingInCheck(unit_->color());
    checkMatedKing_ = board_->isKingCheckMated(unit_->color());
    staleMatedKing_ = board_->isKingStalemated(unit_->color());

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

  bool checkedKing_;
  bool staleMatedKing_;
  bool checkMatedKing_;
};