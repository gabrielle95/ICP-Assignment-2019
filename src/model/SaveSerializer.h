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
  static commandVector_t deserializeLine_(std::string line, boardPtr_t board);
  static commandPtr_t deserializeCommand_(std::string subst, boardPtr_t board, color_t drawColor);

  static unitType_t unitTypeFrom_(char c);
  static std::string strFrom_(unitType_t unitType);

  static letter_t letterCoordFrom_(char letter);
  static std::string letterStrFrom_(letter_t letter);

  static bool isCharacterUnitType_(char c);
  static bool isCharacterColumnCoord_(char c);
  static bool isCharacterRowCoord_(char c);
  static bool isCharacterSpecialEvent_(char c); // capture, check, mate

};