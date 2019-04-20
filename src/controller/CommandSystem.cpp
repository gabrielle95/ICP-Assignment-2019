#include "CommandSystem.h"

CommandSystem::CommandSystem() {}

void CommandSystem::executeCommand(commandPtr_t command)
{
    redoVector_ = commandVector_t();
    command->execute();
    undoVector_.push_back(command);
}

commandPtr_t CommandSystem::undo()
{

    if (undoVector_.empty())
    {
        return nullptr;
    }

    undoVector_.back()->undo();
    redoVector_.push_back(undoVector_.back());
    undoVector_.pop_back();
    return redoVector_.back();
}

commandPtr_t CommandSystem::redo()
{
    if (redoVector_.empty())
    {
        return nullptr;
    }

    redoVector_.back()->redo();
    undoVector_.push_back(redoVector_.back());
    redoVector_.pop_back();
    return undoVector_.back();
}

commandVector_t CommandSystem::constructCommandsToSave()
{
    commandsToSave_.clear();
    commandsToSave_.insert(commandsToSave_.end(), undoVector_.begin(), undoVector_.end());
    commandsToSave_.insert(commandsToSave_.end(), redoVector_.begin(), redoVector_.end());
    return commandsToSave_;
}
