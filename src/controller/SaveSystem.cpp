#include "SaveSystem.h"
#include "../common/ChessException.h"

SaveSystem::SaveSystem() {}

void SaveSystem::setCommandsToSave(commandVector_t commands)
{
    commandsToSave_ = commands;
}

void SaveSystem::setInputToDeserialize(std::string input)
{
    input_ = input;
}

void SaveSystem::serialize()
{
    serializedCommands_ = SaveSerializer::serializeOutput_(commandsToSave_);
}

void SaveSystem::deserialize(boardPtr_t board)
{
    commandsToPlay_ = SaveSerializer::deserializeInput_(input_, board);
}