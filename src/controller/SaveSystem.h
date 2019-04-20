#include "../model/SaveSerializer.h"

using saveSerializerPtr_t = std::shared_ptr<SaveSerializer>;
using saveSystemPtr_t = std::shared_ptr<SaveSystem>;

class SaveSystem
{
public:
  SaveSystem();

  void setCommandsToSave(commandVector_t commands);

  void serialize();

  std::string getSerializedCommands() const
  {
    return serializedCommands_;
  }

private:
  commandVector_t commandsToSave_;

  std::string serializedCommands_;
};