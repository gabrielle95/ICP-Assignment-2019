#include "CommandSystem.h"

CommandSystem::CommandSystem () {}

void CommandSystem::executeCommand(commandPtr_t command) {
    redoVector_ = commandVector_t();
    command->execute();
    undoVector_.push_back(command);
}

void CommandSystem::undo() {

    if(undoVector_.empty()) {
        return;
    }

    undoVector_.back()->undo();
    redoVector_.push_back(undoVector_.back());
    undoVector_.pop_back();
}

void CommandSystem::redo() {
    if(redoVector_.empty()) {
        return;
    }

    redoVector_.back()->redo();
    undoVector_.push_back(redoVector_.back());
    redoVector_.pop_back();
}

commandVector_t CommandSystem::constructCommandsToSave() {
    std::move(undoVector_.begin(), undoVector_.end(), commandsToSave_.begin());
    return commandsToSave_;
}

void CommandSystem::notifyObservers() {
    if(commandsToSave_.empty()) constructCommandsToSave();
    for(observerPtr_t o : observers_) {
        o->onNotify(shared_from_this());
    }
}

void CommandSystem::onNotify(subjectPtr_t subject) {
    std::cout << "CommandSystem has been notified.\n";
}