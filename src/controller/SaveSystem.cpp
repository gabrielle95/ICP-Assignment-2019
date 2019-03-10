#include "SaveSystem.h"
#include "../common/ChessException.h"

SaveSystem::SaveSystem () : currentlyOpen_(nullptr) {}

void SaveSystem::load_(saveFilePtr_t saveFile) {

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
    load_(save);
}

void SaveSystem::save_(saveFilePtr_t saveFile) {
    try {
        saveFile->write_();
    }
    catch(ChessException &e) {
        std::cout << e.what() << "\n";
    }
}

void SaveSystem::save() {
    if(currentlyOpen_)
        save_(currentlyOpen_);
}

void SaveSystem::saveAs(std::string filePath) {
    try {
        currentlyOpen_->writeAs_(filePath);
    }
    catch (ChessException &e) {
        std::cout << e.what() << "\n";
    }
}

saveFilePtr_t SaveSystem::instantiateSaveFile(std::string filePath) {
    return std::make_shared<SaveFile>(filePath);
}