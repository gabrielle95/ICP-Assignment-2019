#include "../model/SaveFile.h"

typedef std::shared_ptr<SaveFile> saveFilePtr_t;

class SaveSystem {
    public:
        SaveSystem ();

        void load(saveFilePtr_t saveFile);
        void load(std::string filePath);

        void save(saveFilePtr_t saveFile);
        void save(std::string filePath);

        saveFilePtr_t instantiateSaveFile(std::string filePath);

        saveFilePtr_t getOpenedSave() const {
            return currentlyOpen_;
        }

    private:
        saveFilePtr_t currentlyOpen_;
};