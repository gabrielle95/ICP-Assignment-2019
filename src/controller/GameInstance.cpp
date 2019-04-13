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
        throw ChessException("GameInstance::onRequestMove unit is nullptr at " + fromPos.to_str());
    if (moveIsValid_(unit, fromPos, toPos))
    {
        commandPtr_t moveCommand = std::make_shared<MoveUnitCommand>(board_, board_->At(fromPos), toPos);
        commandSystem_->executeCommand(moveCommand);
        return true;
    }
    return false;
}

bool GameInstance::moveIsValid_(unitPtr_t unit, Position fromPos, Position toPos)
{
    return board_->checkMoveValidity(unit, fromPos, toPos);
}

std::vector<Position> GameInstance::onRequestAvailableCells(Position from)
{
    return board_->getAvailableCellsForUnit(from);
}

std::vector<Position> GameInstance::onRequestPositionsOfPlayersTurn(bool isWhitesTurn)
{
    return board_->getPositionsOfPlayersTurn(isWhitesTurn);
}

CommandStructure GameInstance::onRequestUndo() {
    commandPtr_t undoCommand = commandSystem_->undo();

    CommandStructure data;

    if(undoCommand != nullptr) {
        data.undoFrom = undoCommand->new_pos();
        data.undoTo = undoCommand->old_pos();

        unitPtr_t captured = undoCommand->capturedUnit();
        if(captured  != nullptr) {
            data.hasCapturedUnit = true;
            data.capturedUnitColor = captured->color();
            data.capturedUnitType = captured->type();
        }
    }

    return data;
}