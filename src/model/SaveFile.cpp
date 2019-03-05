#include "SaveFile.h"
#include "../common/ChessException.h"

SaveFile::SaveFile(std::string sFPath)
: sFPath_(sFPath), isLoaded_(false) {
    assignFileName_();
}

void SaveFile::print() const {
    #ifdef DEBUG
    std::cout << "\n";
    std::cout << "FILENAME: \n";
    std::cout << sFName_ << "\n";
    std::cout << "\n";
    std::cout << "DATA: \n";
    std::cout << sIData_ << "\n";
    std::cout << "\n";
    #endif
}

void SaveFile::load_() {

    iFile_.open(sFPath_, std::ifstream::in);
    if(!iFile_)
        throw ChessException("Failed to load file: " + sFPath_);

    sStream_.clear();
    sStream_ << iFile_.rdbuf();
    sIData_ = sStream_.str();

    generatedCommands_ = deserializeInput_();

    iFile_.close();
    isLoaded_ = true;
}

void SaveFile::write_() {
    oFile_.open(sFPath_, std::ofstream::trunc);

    if(!oFile_)
        throw ChessException("Failed to save file: " + sFPath_);

    sStream_.clear();
    oFile_ << sOData_;

    oFile_.close();
}

void SaveFile::writeAs_(std::string fileName) {
    sFPath_ = fileName;
    assignFileName_();

    // CONSTRUCT OUTPUT DATA PROPERLY
    sOData_ = sIData_;

    write_();
}

void SaveFile::serializeOutput_(commandVector_t outputCommands) {

}

void SaveFile::serializeLine_(commandPtr_t command) {

}

commandVector_t SaveFile::deserializeInput_() {

    commandVector_t commands;

    std::vector<std::string> lines;
    std::string s;

    while(std::getline(sStream_, s)) {
        lines.push_back(s);
    }

    if(lines.empty()) {
        throw ChessException("The save file is empty.");
    }

    for(auto line : lines) {
        deserializeLine_(line);
    }

    return commands;
}

commandPtr_t SaveFile::deserializeLine_(std::string line) {

    commandPtr_t command;

    for(auto i : line) {
        //std::cout << i << "\n";
    }

    return command;
}

unitType_t SaveFile::unitTypeFrom_(char c) {
    switch (c)
    {
        case 'K': return unitType_t::KING;
        case 'D': return unitType_t::QUEEN;
        case 'V': return unitType_t::ROOK;
        case 'S': return unitType_t::BISHOP;
        case 'J': return unitType_t::KNIGHT;
        case 'p': return unitType_t::PAWN;
        default:
            throw ChessException("Unknown Unit Type");
    }
}

char SaveFile::charFrom_(unitType_t unitType) {
    switch (unitType)
    {
        case unitType_t::KING: return 'K';
        case unitType_t::QUEEN: return 'D';
        case unitType_t::ROOK: return 'V';
        case unitType_t::BISHOP: return 'S';
        case unitType_t::KNIGHT: return 'J';
        case unitType_t::PAWN: return 'p';
        default:
            throw ChessException("Unit Type supplied not part of enum unitType_t.");
    }
}

letter_t SaveFile::letterCoordFrom_(char letter) {
    switch (letter)
    {
        case 'a': return letter_t::A;
        case 'b': return letter_t::B;
        case 'c': return letter_t::C;
        case 'd': return letter_t::D;
        case 'e': return letter_t::E;
        case 'f': return letter_t::F;
        case 'g': return letter_t::G;
        case 'h': return letter_t::H;
        default:
            throw ChessException("No letter coordinate.");
    }
}

char SaveFile::letterCharFrom_(letter_t letter) {
    switch (letter)
    {
        case letter_t::A: return 'a';
        case letter_t::B: return 'b';
        case letter_t::C: return 'c';
        case letter_t::D: return 'd';
        case letter_t::E: return 'e';
        case letter_t::F: return 'f';
        case letter_t::G: return 'g';
        case letter_t::H: return 'h';
        default:
            throw ChessException("Letter supplied not part of enum letter_t.");
    }
}

void SaveFile::assignFileName_() {
    size_t fnamePos = sFPath_.rfind('/');

    #ifdef WIN32
    if(fnamePos == std::string::npos) {
        fnamePos = sFPath_.rfind('\\');
    }
    #endif

    if(fnamePos != std::string::npos) {
        sFName_ = sFPath_.substr(fnamePos + 1);
    }
    else {
        sFName_ = sFPath_;
    }
}