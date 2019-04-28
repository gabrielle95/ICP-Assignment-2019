#pragma once

#include <iostream>
#include <stack>
#include <memory>
#include <vector>
#include "../command/ICommand.h"

using commandPtr_t = std::shared_ptr<ICommand>;
using commandVector_t = std::vector<commandPtr_t>;
using commandSystemPtr_t = std::shared_ptr<CommandSystem>;

class CommandSystem
{
public:
  CommandSystem();

  commandPtr_t executeRecordedCommand();

  commandPtr_t backward();

  void executeCommand(commandPtr_t command);

  commandPtr_t undo();

  commandPtr_t redo();

  commandPtr_t forward();

  commandVector_t constructCommandsToSave();

  void setRecordedSteps(commandVector_t deserializedSteps)
  {
    recordedSteps_ = deserializedSteps;
    recordedStepsIterator_ = recordedSteps_.begin();
  }

  void clearCache()
  {
    recordedSteps_.clear();
    recordedStepsIterator_ = recordedSteps_.begin();
    commandsToSave_.clear();
  }

  bool isGameFinished() const
  {

    if(!undoVector_.empty())
    {
      for(auto &c: undoVector_)
      {
        if(c->mated())
          return true;
      }
    }

    if(!recordedSteps_.empty())
    {
      for(auto &c: recordedSteps_)
      {
        if(c->mated())
          return true;
      }
    }

    return false;
  }

private:
  commandVector_t undoVector_;
  commandVector_t redoVector_;
  commandVector_t commandsToSave_;

  commandVector_t recordedSteps_;
  commandVector_t::iterator recordedStepsIterator_;
};