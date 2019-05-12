/*
 * @file Application.cpp
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

std::vector<Position> Application::onRequestPositionsOfPlayersTurn(int gameId, bool isWhitesTurn)
{
    auto gameIdx = findGameIdx_(gameId);
    if (games_.at(gameIdx) != nullptr)
    {
        return games_.at(gameIdx)->onRequestPositionsOfPlayersTurn(isWhitesTurn);
    }
    return std::vector<Position>();
}

CommandStructure Application::onRequestUndo(int gameId)
{
    auto gameIdx = findGameIdx_(gameId);
    if (games_.at(gameIdx) != nullptr)
    {
        return games_.at(gameIdx)->onRequestUndo();
    }
    return CommandStructure();
}

CommandStructure Application::onRequestRedo(int gameId)
{
    auto gameIdx = findGameIdx_(gameId);
    if (games_.at(gameIdx) != nullptr)
    {
        return games_.at(gameIdx)->onRequestRedo();
    }
    return CommandStructure();
}

std::string Application::onRequestSerializedData(int gameId)
{
    auto gameIdx = findGameIdx_(gameId);
    if (games_.at(gameIdx) != nullptr)
    {
        return games_.at(gameIdx)->onRequestSerializedData();
    }
    return std::string("");
}

void Application::onRequestDeserializedData(int gameId, std::string input)
{
    if(input.empty()) return;

    auto gameIdx = findGameIdx_(gameId);
    if (games_.at(gameIdx) != nullptr)
    {
        games_.at(gameIdx)->onRequestDeserializedData(input);
    }
}

CommandStructure Application::onRequestForward(int gameId)
{
    auto gameIdx = findGameIdx_(gameId);
    if (games_.at(gameIdx) != nullptr)
    {
        return games_.at(gameIdx)->onRequestForward();
    }
    return CommandStructure();
}

CommandStructure Application::onRequestBackward(int gameId)
{
    auto gameIdx = findGameIdx_(gameId);
    if (games_.at(gameIdx) != nullptr)
    {
        return games_.at(gameIdx)->onRequestBackward();
    }
    return CommandStructure();
}

bool Application::onRequestRestart(int gameId)
{
    auto gameIdx = findGameIdx_(gameId);
    if (games_.at(gameIdx) != nullptr)
    {
        return games_.at(gameIdx)->onRequestRestart();
    }
    return false;
}

bool Application::isGameFinished(int gameId)
{
    auto gameIdx = findGameIdx_(gameId);
    if (games_.at(gameIdx) != nullptr)
    {
        return games_.at(gameIdx)->isGameFinished();
    }
    return false;
}