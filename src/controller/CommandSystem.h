#pragma once

#include <iostream>
#include <stack>
#include <memory>
#include <vector>
#include "../observer/ISubject.h"
#include "../command/ICommand.h"

using commandPtr_t = std::shared_ptr<ICommand>;
using commandVector_t = std::vector<commandPtr_t>;
using commandSystemPtr_t = std::shared_ptr<CommandSystem>;

class CommandSystem : public ISubject, public IObserver, public std::enable_shared_from_this<CommandSystem> {
    public:

        CommandSystem();

        void executeCommand(commandPtr_t command);

        void undo();

        void redo();

        commandVector_t constructCommandsToSave();

        virtual void notifyObservers();

        virtual void onNotify(subjectPtr_t subject);

        virtual void printNotification() {
            std::cout << "CommandSystem called from SaveSystem\n";
        }

    private:
        commandVector_t undoVector_;
        commandVector_t redoVector_;
        commandVector_t commandsToSave_;
};