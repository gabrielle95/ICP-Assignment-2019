/*
 * @file ICommand.h
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

#include "../common/Position.h"
#include "../model/Unit.h"

class CommandSystem;
class SaveSerializer;

/**
 * @brief An interface of a game command
 *
 */
class ICommand
{
public:
  virtual Position old_pos() const = 0;
  virtual Position new_pos() const = 0;
  virtual unitPtr_t capturedUnit() const = 0;
  virtual unitPtr_t movingUnit() const = 0;
  virtual bool checked() const = 0;
  virtual bool mated() const = 0;

protected:
  friend CommandSystem;
  friend SaveSerializer;

  virtual void execute() = 0;
  virtual void undo() = 0;
  virtual void redo() = 0;
};