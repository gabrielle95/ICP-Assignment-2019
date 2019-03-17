#include "Application.h"


Application::Application () : gameInstanceNextId_(0) {
}

void Application::newGame(int gameId) {
    games_.emplace_back(std::make_shared<GameInstance>(gameId));
}

void Application::quitGame(int gameId) {
    int idx = findGame_(gameId);
    games_.erase(games_.begin() + idx);
}

int Application::findGame_(int gameId) {

    auto it = std::find_if(games_.begin(), games_.end(), [&](gameInstancePtr_t const& game) {
        return game->Id() == gameId;
    });

    return std::distance(games_.begin(), it);
}

GameInstance::GameInstance(int id) : gameId_(id) {
    commandSystem = std::make_shared<CommandSystem>();
    saveSystem = std::make_shared<SaveSystem>();
}
