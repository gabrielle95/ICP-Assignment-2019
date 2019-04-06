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
        isCapturer_(false)
  {
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
    }
    board_->moveUnit(unit_, pos_);
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
};