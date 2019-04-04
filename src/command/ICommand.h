#pragma once

class CommandSystem;

class ICommand
{
  protected:
    friend CommandSystem;

    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
};