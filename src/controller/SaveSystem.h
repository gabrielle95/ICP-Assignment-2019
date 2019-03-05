#include "../observer/ISubject.h"
#include "../model/SaveFile.h"

using saveFilePtr_t = std::shared_ptr<SaveFile>;
using saveSystemPtr_t = std::shared_ptr<SaveSystem>;

class SaveSystem : public ISubject, public IObserver, public std::enable_shared_from_this<SaveSystem> {
    public:
        SaveSystem ();

        void load(std::string filePath);

        void save();

        void saveAs(std::string filePath);

        saveFilePtr_t instantiateSaveFile(std::string filePath);

        saveFilePtr_t getOpenedSave() const {
            return currentlyOpen_;
        }

        virtual void notifyObservers();

        virtual void onNotify(subjectPtr_t subject);

        virtual void printNotification() {}

    private:

        void load_(saveFilePtr_t saveFile);
        void save_(saveFilePtr_t saveFile);
        saveFilePtr_t currentlyOpen_; //TODO
};