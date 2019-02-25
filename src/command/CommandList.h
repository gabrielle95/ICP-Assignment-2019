#pragma once

#include <vector>
#include "Command.h"

class CommandList {
    public:

        CommandList();
        ~CommandList();

        bool isEmpty();

        void append(Command *command);

        Command * previous();

        Command * next();

        Command * current();

    private:

        void moveCurrentIdx_();

        std::vector<Command *> cmdList_;
        int curr_idx_;
        int prev_idx_;
        int next_idx_;
};