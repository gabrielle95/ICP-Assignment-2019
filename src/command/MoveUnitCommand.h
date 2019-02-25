#pragma once

#include "../view/Unit.h"
#include "Command.h"

class MoveUnitCommand : public Command {
    public:
        MoveUnitCommand(Unit *unit, int x, int y)
        : unit_(unit),
        x_(x),
        y_(y)
        {}

        virtual void execute() {
            unit_->moveTo(x_, y_);
        }


    private:
        Unit* unit_;
        int x_;
        int y_;

};