#pragma once

#include "../common/Position.h"
#include "../model/Unit.h"

class CommandSystem;
class SaveSerializer;

class ICommand
{
public:
  virtual Position old_pos() const = 0;
  virtual Position new_pos() const = 0;
  virtual unitPtr_t capturedUnit() const = 0;
  virtual unitPtr_t movingUnit() const = 0;

protected:
  friend CommandSystem;
  friend SaveSerializer;

  virtual void execute() = 0;
  virtual void undo() = 0;
  virtual void redo() = 0;
};