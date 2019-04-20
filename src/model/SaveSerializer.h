#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include "Unit.h"
#include "../controller/CommandSystem.h"
#include "../model/Board.h"

class SaveSystem;

class SaveSerializer
{
private:
  friend SaveSystem;

  static std::string serializeOutput_(commandVector_t outputCommands);
  static std::string serializeCommand_(commandPtr_t command);

  static commandVector_t deserializeInput_(std::string input, boardPtr_t board);
  static commandPtr_t deserializeLine_(std::string line, boardPtr_t board);

  static unitType_t unitTypeFrom_(std::string c);
  static std::string strFrom_(unitType_t unitType);

  static letter_t letterCoordFrom_(char letter);
  static std::string letterStrFrom_(letter_t letter);
};