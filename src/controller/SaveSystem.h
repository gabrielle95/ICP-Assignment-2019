/*
 * @file SaveSystem.h
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
#include "../model/SaveSerializer.h"

using saveSerializerPtr_t = std::shared_ptr<SaveSerializer>;
using saveSystemPtr_t = std::shared_ptr<SaveSystem>;

class SaveSystem
{
public:

  /**
   * @brief Construct a new Save System object
   *
   */
  SaveSystem();

  /**
   * @brief Set the Commands To Save
   *
   * @param commands The commands to be serialized
   */
  void setCommandsToSave(commandVector_t commands);

  /**
   * @brief Set the Input To Deserialize
   *
   * @param input The input from which commands will be generated
   */
  void setInputToDeserialize(std::string input);

  /**
   * @brief Serializes the set commands
   *
   */
  void serialize();

  /**
   * @brief Deserializes the set input
   *
   * @param board The game board state for reference
   */
  void deserialize(boardPtr_t board);

  std::string getSerializedCommands() const
  {
    return serializedCommands_;
  }

  /**
   * @brief Get the Deserialized Commands
   *
   * @return commandVector_t The command vector with generated commands
   */
  commandVector_t getDeserializedCommands() const
  {
    return commandsToPlay_;
  }

  /**
   * @brief Clears the cache of the containers
   *
   */
  void clearCache() {
    commandsToSave_.clear();
    commandsToPlay_.clear();
    input_.clear();
    serializedCommands_.clear();
  }

private:
  commandVector_t commandsToSave_;
  std::string serializedCommands_;

  std::string input_;
  commandVector_t commandsToPlay_;
};