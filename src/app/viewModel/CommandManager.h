#pragma once

#include <vector>
#include "Command.h"

class CommandManager {
    public:

        CommandManager() {
            this->current_ = nullptr;
            this->prev_ = nullptr;
            this->next_ = nullptr;
        }

        Command * currentCommand() {
            return this->current_;
        }

        void undo() {

        }

        void redo() {

        }

        void appendCommand(Command *command) {
            this->cmdList_.emplace_back(command);
            this->prev_ = this->current_;
            this->current_ = this->cmdList_.back();
        }

    private:
        std::vector<Command *> cmdList_;
        Command * current_;
        Command * prev_;
        Command * next_;
};