#include "CommandSystem.h"

CommandSystem::CommandSystem() {}

commandPtr_t CommandSystem::executeRecordedCommand()
{
    if (recordedSteps_.empty())
        return nullptr;
    if (recordedStepsIterator_ == recordedSteps_.end())
        return nullptr;
    if (!undoVector_.empty())
        return nullptr;

    commandPtr_t command = (*recordedStepsIterator_);
    command->execute();
    ++recordedStepsIterator_;

    return command;
}

commandPtr_t CommandSystem::backward()
{
    if (!undoVector_.empty())
        return nullptr;
    if (recordedSteps_.empty())
        return nullptr;
    if (recordedStepsIterator_ - 1 < recordedSteps_.begin())
        return nullptr;


    commandPtr_t command = (*(--recordedStepsIterator_));
    if (command)
    {
        command->undo();
    }
    return command;
}

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
    commandsToSave_.insert(commandsToSave_.end(), recordedSteps_.begin(), recordedStepsIterator_);
    commandsToSave_.insert(commandsToSave_.end(), undoVector_.begin(), undoVector_.end());

    return commandsToSave_;
}
