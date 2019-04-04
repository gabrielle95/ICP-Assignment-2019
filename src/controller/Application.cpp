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