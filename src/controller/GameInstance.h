#pragma once

#include <vector>
#include <memory>
#include <vector>
#include <algorithm>
#include "CommandSystem.h"
#include "../command/MoveUnitCommand.h"
#include "SaveSystem.h"
#include "../model/Board.h"
#include "../common/CommandStructure.h"

class GameInstance
{
public:
  GameInstance(int id);

  int Id() const
  {
    return gameId_;
  }

  bool onRequestMove(Position fromPos, Position toPos);
  std::vector<Position> onRequestAvailableCells(Position from);
  std::vector<Position> onRequestPositionsOfPlayersTurn(bool isWhitesTurn);
  CommandStructure onRequestUndo();
  CommandStructure onRequestRedo();
  std::string onRequestSerializedData();

private:
  bool moveIsValid_(unitPtr_t unit, Position fromPos, Position toPos);

  int gameId_;
  commandSystemPtr_t commandSystem_;
  saveSystemPtr_t saveSystem_;
  boardPtr_t board_;
};