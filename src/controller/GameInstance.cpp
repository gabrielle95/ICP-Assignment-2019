/*
 * @file GameInstance.cpp
 *
 * Project name:
 * Chess 2019
 *
 * Description:
 * http://www.fit.vutbr.cz/study/courses/ICP/public/ICP-PRJ-zadani.html.cs
 *
 * Team:
 * @author Gabriela Pacakova (xpacak01)
 * @author Adam Lanicek (xlanic04)
 */
#include "../common/ChessException.h"
#include "GameInstance.h"

GameInstance::GameInstance(int id) : gameId_(id)
{
    commandSystem_ = std::make_shared<CommandSystem>();
    saveSystem_ = std::make_shared<SaveSystem>();
    board_ = std::make_shared<Board>();
}

bool GameInstance::onRequestMove(Position fromPos, Position toPos)
{
    unitPtr_t unit = board_->At(fromPos);

    // rewrite this line pls
    if (unit == nullptr)
        throw ChessException("GameInstance::onRequestMove unit is nullptr.");
    if (moveIsValid_(toPos))
    {
        commandPtr_t moveCommand = std::make_shared<MoveUnitCommand>(board_, board_->At(fromPos), toPos);
        commandSystem_->executeCommand(moveCommand);
        return true;
    }
    return false;
}

bool GameInstance::moveIsValid_(Position toPos)
{
    return board_->checkMoveValidity(toPos);
}

std::vector<Position> GameInstance::onRequestAvailableCells(Position from)
{
    return board_->getAvailableCellsForUnit(from);
}

std::vector<Position> GameInstance::onRequestPositionsOfPlayersTurn(bool isWhitesTurn)
{
    return board_->getPositionsOfPlayersTurn(isWhitesTurn);
}

CommandStructure GameInstance::onRequestUndo()
{
    commandPtr_t undoCommand = commandSystem_->undo();

    CommandStructure data;

    if (undoCommand != nullptr)
    {
        data.undoFrom = undoCommand->new_pos();
        data.undoTo = undoCommand->old_pos();

        unitPtr_t captured = undoCommand->capturedUnit();
        if (captured != nullptr)
        {
            data.hasCapturedUnit = true;
            data.capturedUnitColor = captured->color();
            data.capturedUnitType = captured->type();
        }
    }

    return data;
}

CommandStructure GameInstance::onRequestRedo()
{

    commandPtr_t redoCommand = commandSystem_->redo();

    CommandStructure data;

    if (redoCommand != nullptr)
    {
        data.redoFrom = redoCommand->old_pos();
        data.redoTo = redoCommand->new_pos();
    }

    return data;
}

std::string GameInstance::onRequestSerializedData()
{
    // clear all
    saveSystem_->clearCache();

    saveSystem_->setCommandsToSave(commandSystem_->constructCommandsToSave());

    saveSystem_->serialize();

    return saveSystem_->getSerializedCommands();
}

void GameInstance::onRequestDeserializedData(std::string input)
{
    // reset board before "simulation"
    board_->resetBoard();

    // clear the previously recorded steps
    commandSystem_->clearCache();

    // save system clear
    saveSystem_->clearCache();

    saveSystem_->setInputToDeserialize(input);

    try {
        saveSystem_->deserialize(board_);
    }
    catch(ChessException& e) {
        std::cerr << e.what() << "\n";
        board_->resetBoard();
        commandSystem_->clearCache();
        saveSystem_->clearCache();
    }

    commandSystem_->setRecordedSteps(saveSystem_->getDeserializedCommands());

    // reset board after "simulation"
    board_->resetBoard();
}

CommandStructure GameInstance::onRequestForward()
{
    commandPtr_t command = commandSystem_->executeRecordedCommand();

    CommandStructure data;

    if (command != nullptr)
    {
        data.redoFrom = command->old_pos();
        data.redoTo = command->new_pos();
    }

    return data;
}

CommandStructure GameInstance::onRequestBackward()
{
    commandPtr_t backCommand = commandSystem_->backward();

    CommandStructure data;

    if (backCommand != nullptr)
    {
        data.undoFrom = backCommand->new_pos();
        data.undoTo = backCommand->old_pos();

        unitPtr_t captured = backCommand->capturedUnit();
        if (captured != nullptr)
        {
            data.hasCapturedUnit = true;
            data.capturedUnitColor = captured->color();
            data.capturedUnitType = captured->type();
        }
    }

    return data;
}

bool GameInstance::onRequestRestart()
{
    bool restarted = commandSystem_->restartSteps();
    if(restarted)
    {
        board_->resetBoard();
    }
    return restarted;
}

bool GameInstance::isGameFinished()
{
    return board_->isGameFinished();
}
