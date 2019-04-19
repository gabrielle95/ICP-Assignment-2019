#pragma once

#include "GameInstance.h"

using appPtr_t = std::unique_ptr<class Application>;
using gameInstancePtr_t = std::shared_ptr<GameInstance>;

class Application
{
public:
  Application();
  void newGame(int gameId);
  void quitGame(int gameId);
  bool onRequestMove(int gameId, Position from, Position to);
  std::vector<Position> onRequestAvailableCells(int gameId, Position from);
  std::vector<Position> onRequestPositionsOfPlayersTurn(int gameId, bool isWhitesTurn);
  CommandStructure onRequestUndo(int gameId);
  CommandStructure onRequestRedo(int gameId);

private:
  int findGameIdx_(int gameId);
  std::vector<gameInstancePtr_t> games_;
  int gameInstanceNextId_;
};