#pragma once

#include <stack>
#include <memory>
#include <../command/ICommand.h>

typedef std::shared_ptr<ICommand> commandPtr_t;
typedef std::stack<commandPtr_t> commandStack_t;

class CommandSystem {
    public:

        CommandSystem();

        void executeCommand(commandPtr_t command);

        void undo();

        void redo();


    private:
        commandStack_t undoStack_;
        commandStack_t redoStack_;

};