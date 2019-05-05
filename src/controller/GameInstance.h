/*
 * @file GameInstance.h
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

  /**
   * @brief Construct a new Game Instance object
   *
   * @param id The id of a new game instance
   */
  GameInstance(int id);

  /**
   * @brief Gets the game instance id
   *
   * @return int The game instance id
   */
  int Id() const
  {
    return gameId_;
  }

  /**
   * @brief Handles the move request passed from application
   *
   * @param fromPos The position from which unit moves
   * @param toPos The position to which unit moves
   * @return true The request is valid
   * @return false The request is invalid
   */
  bool onRequestMove(Position fromPos, Position toPos);

  /**
   * @brief Handles the available cells request
   *
   * @param from From which position to calculate the cells
   * @return std::vector<Position> The available positions
   */
  std::vector<Position> onRequestAvailableCells(Position from);

  /**
   * @brief Handles the request for positions of units of a certain team (color)
   *
   * @param isWhitesTurn Whether its the white players turn (determines the team)
   * @return std::vector<Position> The positions of units of a certain team (black or white)
   */
  std::vector<Position> onRequestPositionsOfPlayersTurn(bool isWhitesTurn);

  /**
   * @brief Handles the undo request
   *
   * @return CommandStructure A data structure with undo positions
   */
  CommandStructure onRequestUndo();

  /**
   * @brief Handles the redo request
   *
   * @return CommandStructure A data structure with redo positions
   */
  CommandStructure onRequestRedo();

  /**
   * @brief Handles the game serialization from commands
   *
   * @return std::string The serialized command data
   */
  std::string onRequestSerializedData();

  /**
   * @brief Handles the game deserialization into commands
   *
   * @param input The loaded save game data
   */
  void onRequestDeserializedData(std::string input);

  /**
   * @brief Handles the request to move one step forward
   *
   * @return CommandStructure A data structure containing the command positions about the forward move
   */
  CommandStructure onRequestForward();

  /**
   * @brief Handles the request to move one step backward
   *
   * @return CommandStructure A data structure containing the command positions about the backward move
   */
  CommandStructure onRequestBackward();

  /**
   * @brief A request to check for the finishing condition
   *
   * @return true The checkmate event has occured and game is finished
   * @return false The checkmate event has not occured and the game is not finished
   */
  bool isGameFinished();

private:
  bool moveIsValid_(unitPtr_t unit, Position fromPos, Position toPos);

  int gameId_;
  commandSystemPtr_t commandSystem_;
  saveSystemPtr_t saveSystem_;
  boardPtr_t board_;
};