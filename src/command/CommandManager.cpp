#include "CommandManager.h"

CommandManager::CommandManager () {
    this->userCommands_ = new CommandList();
    this->loadedCommands_ = new CommandList();
}

// rewrite this
void CommandManager::user_undo () {
    Command * prev = this->userCommands_->previous();
    if(prev) {
        prev->execute();
        // check for new current and prev, if there is no prev
        // notify to disable undo button
    }
}

void CommandManager::user_redo () {
    Command * next = this->userCommands_->next();
    if(next) {
        next->execute();
        // check for new current and next, if there is no next
        // notify to disable redo button
    }
}