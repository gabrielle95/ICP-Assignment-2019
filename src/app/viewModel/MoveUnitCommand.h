#pragma once

#include "../model/Unit.h"
#include "Command.h"

class MoveUnitCommand : public Command {
    public:
        MoveUnitCommand(Unit *unit, int x, int y)
        : unit_(unit),
        x_(x),
        y_(y)
        //xOld_(0),
        //yOld_(0)
        {}

        virtual void execute() {
            //xOld_= unit_->x();
            //yOld_ = unit_->y();
            unit_->moveTo(x_, y_);
        }

        /*virtual void undo() {
            unit_->moveTo(xOld_, yOld_, true);
        }*/

    private:
        Unit* unit_;
        int x_;
        int y_;

        //int xOld_;
        //int yOld_;
};