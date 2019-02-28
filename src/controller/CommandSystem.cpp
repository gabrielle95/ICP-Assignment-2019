#include "CommandSystem.h"

CommandSystem::CommandSystem () {}

void CommandSystem::executeCommand(commandPtr_t command) {
    redoStack_ = commandStack_t();
    command->execute();
    undoStack_.push(command);
}

void CommandSystem::undo() {

    if(undoStack_.empty()) {
        return;
    }

    undoStack_.top()->undo();
    redoStack_.push(undoStack_.top());
    undoStack_.pop();
}

void CommandSystem::redo() {
    if(redoStack_.empty()) {
        return;
    }

    redoStack_.top()->redo();
    undoStack_.push(redoStack_.top());
    redoStack_.pop();
}