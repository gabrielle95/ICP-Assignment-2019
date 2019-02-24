#pragma once

#include "../model/Unit.h"

class Command {

    public:
        virtual ~Command();
        virtual void execute(Unit& unit) = 0;
        virtual void undo() = 0;
        virtual void redo() = 0;
};