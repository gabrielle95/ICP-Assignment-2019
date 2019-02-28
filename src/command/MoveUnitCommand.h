#pragma once

#include "../model/Unit.h"
#include "ICommand.h"

class MoveUnitCommand : public ICommand {
    public:
        MoveUnitCommand(unitPtr_t unit, Position pos)
        :
        unit_(unit),
        pos_(pos)
        {}

        virtual void execute() {
            pos_old_ = unit_->getPos();
            unit_->moveTo(pos_);
        }

        virtual void undo () {
            unit_->moveTo(pos_old_);
        }

        virtual void redo () {
            unit_->moveTo(pos_);
        }

    private:
        unitPtr_t unit_;
        Position pos_;
        Position pos_old_;
};