#pragma once

#include "CommandList.h"

class CommandManager {
    public:

        CommandManager();

        void user_undo();

        void user_redo();

        void step_forward();

        void step_backward();

        /**
         * @brief
         * Appends new player command to the end of the vector.
         * Points at it as current.
         * @param command Command to be appended.
         */
        void appendUserCommand(Command * command);

    private:
        CommandList * userCommands_;
        CommandList * loadedCommands_;
};