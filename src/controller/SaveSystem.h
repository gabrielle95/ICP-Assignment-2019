#include "../model/SaveSerializer.h"

using saveSerializerPtr_t = std::shared_ptr<SaveSerializer>;
using saveSystemPtr_t = std::shared_ptr<SaveSystem>;

class SaveSystem
{
public:
  SaveSystem();

  void setCommandsToSave(commandVector_t commands);

  void setInputToDeserialize(std::string input);

  void serialize();

  void deserialize(boardPtr_t board);

  std::string getSerializedCommands() const
  {
    return serializedCommands_;
  }

  commandVector_t getDeserializedCommands() const
  {
    return commandsToPlay_;
  }

private:
  commandVector_t commandsToSave_;
  std::string serializedCommands_;

  std::string input_;
  commandVector_t commandsToPlay_;
};