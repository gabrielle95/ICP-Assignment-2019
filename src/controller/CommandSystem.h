/*
 * @file CommandSystem.h
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

#include <iostream>
#include <stack>
#include <memory>
#include <vector>
#include "../command/ICommand.h"

using commandPtr_t = std::shared_ptr<ICommand>;
using commandVector_t = std::vector<commandPtr_t>;
using commandSystemPtr_t = std::shared_ptr<CommandSystem>;

/**
 * @brief A class that directs the command execution, redo and undo logic
 *
 */
class CommandSystem
{
public:

  /**
   * @brief Construct a new Command System object
   *
   */
  CommandSystem();

  /**
   * @brief Executes a command generated from a save file
   *
   * @return commandPtr_t The executed command
   */
  commandPtr_t executeRecordedCommand();

  /**
   * @brief Performs the command backward
   *
   * @return commandPtr_t The executed backward command
   */
  commandPtr_t backward();

  /**
   * @brief Performs the command forward
   *
   * @return commandPtr_t The executed forward command
   */
  commandPtr_t forward();

  /**
   * @brief Executes a user performed command
   *
   * @param command The executed command
   */
  void executeCommand(commandPtr_t command);

  /**
   * @brief Performs an undo operation on user executed commands
   *
   * @return commandPtr_t The executed undo command
   */
  commandPtr_t undo();

  /**
   * @brief Performs a redo operation on user executed commands
   *
   * @return commandPtr_t The executed redo command
   */
  commandPtr_t redo();

  /**
   * @brief Creates a vector of all the commands to serialize
   *
   * @return commandVector_t The commands to serialize
   */
  commandVector_t constructCommandsToSave();

  /**
   * @brief Sets the loaded steps as the steps to perform forward and backward on
   *
   * @param deserializedSteps The deserialized steps from the SaveSystem to set
   */
  void setRecordedSteps(commandVector_t deserializedSteps)
  {
    recordedSteps_ = deserializedSteps;
    recordedStepsIterator_ = recordedSteps_.begin();
    recordedStepsForRestart_ = recordedSteps_;
  }

  /**
   * @brief Clears all the cached steps and moves the recorded steps iterator to the beginning
   *
   */
  void clearCache()
  {
    recordedSteps_.clear();
    recordedStepsIterator_ = recordedSteps_.begin();
    commandsToSave_.clear();
  }

  /**
   * @brief Sets the steps to the beginning
   *
   * @return true Steps were restarted
   * @return false No loaded steps to restart
   */
  bool restartSteps()
  {
    if(recordedStepsForRestart_.empty()) return false;
    recordedSteps_ = recordedStepsForRestart_;
    recordedStepsIterator_ = recordedSteps_.begin();
    commandsToSave_.clear();
    return true;
  }

  /**
   * @brief Checks for a finishing condition looking for a checkmate flag in commands
   *
   * @return true The game is finished
   * @return false The game is not finished
   */
  bool isGameFinished() const
  {
    if(!undoVector_.empty())
    {
      for(auto &c: undoVector_)
      {
        if(c->mated())
          return true;
      }
      //return false;
    }

    /*if(!recordedSteps_.empty())
    {
      for(auto &c: recordedSteps_)
      {
        if(c->mated())
          return true;
      }
      return false;
    }*/
    return false;
  }

private:
  commandVector_t undoVector_;
  commandVector_t redoVector_;
  commandVector_t commandsToSave_;

  commandVector_t recordedSteps_;
  commandVector_t::iterator recordedStepsIterator_;
  commandVector_t recordedStepsForRestart_;
};