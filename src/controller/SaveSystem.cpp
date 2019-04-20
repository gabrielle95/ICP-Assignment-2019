#include "SaveSystem.h"
#include "../common/ChessException.h"

SaveSystem::SaveSystem() {}

void SaveSystem::setCommandsToSave(commandVector_t commands)
{
    commandsToSave_ = commands;
}

void SaveSystem::serialize()
{
    serializedCommands_ = SaveSerializer::serializeOutput_(commandsToSave_);
}