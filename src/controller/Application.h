/*
 * @file Application.h
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

#include "GameInstance.h"

using appPtr_t = std::unique_ptr<class Application>;
using gameInstancePtr_t = std::shared_ptr<GameInstance>;

/**
 * @brief Class representing the whole application instance
 *
 */
class Application
{
public:
  /**
   * @brief Construct a new Application object
   *
   */
  Application();

  /**
   * @brief Creates a new game instance
   *
   * @param gameId The id of the game instance
   */
  void newGame(int gameId);

  /**
   * @brief Quits a desired game according to its game id
   *
   * @param gameId The id of the game instance
   */
  void quitGame(int gameId);

  /**
   * @brief Handles a unit move request from the GUI
   *
   * @param gameId The game instance id the request corresponds to
   * @param from The position from which the unit is moving
   * @param to To position to which unit is moving
   * @return true The request was valid and can be performed
   * @return false The request was invalid and cannot be performed
   */
  bool onRequestMove(int gameId, Position from, Position to);

  /**
   * @brief Handles the request for available moves for a certain unit
   *
   * @param gameId The id of the game
   * @param from The position of the unit to calculate its available positions
   * @return std::vector<Position> The available positions for a given unit standing on from Position
   */
  std::vector<Position> onRequestAvailableCells(int gameId, Position from);

  /**
   * @brief Handles the request for positions of units of a certain team (color)
   *
   * @param gameId The ID of the game
   * @param isWhitesTurn Whether its the white players turn (determines the team)
   * @return std::vector<Position> The positions of units of a certain team (black or white)
   */
  std::vector<Position> onRequestPositionsOfPlayersTurn(int gameId, bool isWhitesTurn);

  /**
   * @brief Handles the undo request
   *
   * @param gameId The id of the game
   * @return CommandStructure A data structure containing undo positions that deals also with captured units
   */
  CommandStructure onRequestUndo(int gameId);

  /**
   * @brief Handles the redo request
   *
   * @param gameId The id of the game
   * @return CommandStructure A data structure containing redo positions for units
   */
  CommandStructure onRequestRedo(int gameId);

  /**
   * @brief Handles the saving of a game, requesting to serialize commands
   *
   * @param gameId The id of the game
   * @return std::string The performed commands serialized in a string
   */
  std::string onRequestSerializedData(int gameId);

  /**
   * @brief Handles the loading of a game, requesting to deserialize data into commands
   *
   * @param gameId The id of the game
   * @param input The loaded save game data
   */
  void onRequestDeserializedData(int gameId, std::string input);

  /**
   * @brief Handles the request to move one step forward
   *
   * @param gameId The id of the game
   * @return CommandStructure A data structure containing the command positions about the forward move
   */
  CommandStructure onRequestForward(int gameId);

  /**
   * @brief Handles the request to move one step backward
   *
   * @param gameId The id of the game
   * @return CommandStructure A data structure containing the command positions about the backward move
   */
  CommandStructure onRequestBackward(int gameId);

  /**
   * @brief A request to check for the finishing condition
   *
   * @param gameId The id of the game
   * @return true The checkmate event has occured and game is finished
   * @return false The checkmate event has not occured and the game is not finished
   */
  bool isGameFinished(int gameId);

private:
  int findGameIdx_(int gameId);
  std::vector<gameInstancePtr_t> games_;
  int gameInstanceNextId_;
};