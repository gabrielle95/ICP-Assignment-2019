#include "SaveSystem.h"
#include "../common/ChessException.h"

SaveSystem::SaveSystem () : currentlyOpen_(nullptr) {}

void SaveSystem::load(saveFilePtr_t saveFile) {

    try {
        saveFile->load_();
    }
    catch(ChessException &e) {
        std::cout << e.what() << "\n";
    }

    if(saveFile->isLoaded()) {
        currentlyOpen_ = saveFile;
    }
}

void SaveSystem::load(std::string filePath) {
    saveFilePtr_t save = instantiateSaveFile(filePath);
    load(save);
}

saveFilePtr_t SaveSystem::instantiateSaveFile(std::string filePath) {
    return std::make_shared<SaveFile>(filePath);
}



