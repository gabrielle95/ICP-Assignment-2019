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

void SaveSystem::notifyObservers() {

    for(observerPtr_t o : observers_) {
        o->onNotify(shared_from_this());
    }
}

void SaveSystem::onNotify(subjectPtr_t subject) {
    std::cout << "SaveSystem has been notified.\n";
    subject->printNotification();
}