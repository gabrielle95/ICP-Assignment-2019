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

    void executeCommand(commandPtr_t command);

    void undo();

    void redo();

    commandVector_t constructCommandsToSave();

  private:
    commandVector_t undoVector_;
    commandVector_t redoVector_;
    commandVector_t commandsToSave_;
};