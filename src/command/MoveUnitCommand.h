#pragma once

#include "../model/Unit.h"
#include "ICommand.h"

class MoveUnitCommand : public ICommand {
    public:
        MoveUnitCommand(unitPtr_t unit, int x, int y)
        :
        unit_(unit),
        x_(x),
        y_(y)
        {}

        virtual void execute() {
            x_old_ = unit_->x();
            y_old_ = unit_->y();
            unit_->moveTo(x_, y_);
        }

        virtual void undo () {
            unit_->moveTo(x_old_, y_old_);
        }

        virtual void redo () {
            unit_->moveTo(x_, y_);
        }

    private:
        unitPtr_t unit_;
        int x_; // new x
        int y_; // new y
        int x_old_;
        int y_old_;
};