#pragma once

#include "../view/Unit.h"

class Command {

    public:
        virtual ~Command();
        virtual void execute() = 0;
};