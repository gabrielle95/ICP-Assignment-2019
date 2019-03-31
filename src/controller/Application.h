#pragma once

#include <memory>
#include <vector>
#include <algorithm>
#include "CommandSystem.h"
#include "../command/MoveUnitCommand.h"
#include "SaveSystem.h"
#include "../model/Board.h"

using appPtr_t = std::unique_ptr<class Application>;
using gameInstancePtr_t = std::shared_ptr<class GameInstance>;

class Application {
    public:
        Application();
        void newGame(int gameId);
        void quitGame(int gameId);
        bool onRequestMove(int gameId, Position from, Position to);
        std::vector<Position> onRequestAvailableCells(int gameId, Position from);

    private:

        int findGameIdx_(int gameId);
        std::vector<gameInstancePtr_t> games_;
        int gameInstanceNextId_;
};

class GameInstance {
    public:

        GameInstance(int id);

        int Id() const {
            return gameId_;
        }

        bool onRequestMove(Position fromPos, Position toPos);
        std::vector<Position> onRequestAvailableCells(Position from);

    private:
        bool moveIsValid_(unitPtr_t unit, Position fromPos, Position toPos);

        int gameId_;
        commandSystemPtr_t commandSystem_;
        saveSystemPtr_t saveSystem_;
        boardPtr_t board_;
};
