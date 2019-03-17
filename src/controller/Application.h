#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include "CommandSystem.h"
#include "SaveSystem.h"

using appPtr_t = std::unique_ptr<class Application>;
using gameInstancePtr_t = std::shared_ptr<class GameInstance>;

class Application {
    public:
        Application();
        void newGame(int gameId);
        void quitGame(int gameId);

    private:

        int findGame_(int gameId);
        std::vector<gameInstancePtr_t> games_;
        int gameInstanceNextId_;
};

class GameInstance {
    public:

        GameInstance(int id);

        int Id() const {
            return gameId_;
        }

    private:
        int gameId_;
        commandSystemPtr_t commandSystem;
        saveSystemPtr_t saveSystem;
};
