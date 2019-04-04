#include "../common/ChessException.h"
#include "Application.h"

Application::Application() : gameInstanceNextId_(0)
{
}

void Application::newGame(int gameId)
{
    games_.emplace_back(std::make_shared<GameInstance>(gameId));
}

void Application::quitGame(int gameId)
{
    int idx = findGameIdx_(gameId);
    games_.erase(games_.begin() + idx);
}

int Application::findGameIdx_(int gameId)
{

    auto it = std::find_if(games_.begin(), games_.end(), [&](gameInstancePtr_t const &game) {
        return game->Id() == gameId;
    });

    return std::distance(games_.begin(), it);
}

bool Application::onRequestMove(int gameId, Position from, Position to)
{
    auto gameIdx = findGameIdx_(gameId);
    if (games_.at(gameIdx) != nullptr)
    {
        return games_.at(gameIdx)->onRequestMove(from, to);
    }
    return false;
}

std::vector<Position> Application::onRequestAvailableCells(int gameId, Position from)
{
    auto gameIdx = findGameIdx_(gameId);
    if (games_.at(gameIdx) != nullptr)
    {
        return games_.at(gameIdx)->onRequestAvailableCells(from);
    }
    return std::vector<Position>();
}

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
