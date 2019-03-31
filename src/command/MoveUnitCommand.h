#pragma once

#include "../model/Board.h"
#include "../model/Unit.h"
#include "ICommand.h"

class MoveUnitCommand : public ICommand {
    public:
        MoveUnitCommand(boardPtr_t board, unitPtr_t unit, Position pos)
        :
        board_(board),
        unit_(unit),
        pos_(pos)
        {}

    private:

        virtual void execute () {
            pos_old_ = board_->findUnitPosition(unit_);
            board_->moveUnit(unit_, pos_);
        }

        virtual void undo () {
            board_->moveUnit(unit_, pos_old_);
        }

        virtual void redo () {
            board_->moveUnit(unit_, pos_);
        }

        boardPtr_t board_;
        unitPtr_t unit_;
        Position pos_;
        Position pos_old_;
};