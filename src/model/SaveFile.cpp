#include "SaveFile.h"
#include "../common/ChessException.h"

SaveFile::SaveFile(std::string sFPath)
: sFPath_(sFPath), isLoaded_(false) {

    size_t fnamePos = sFPath_.rfind('/');

    #ifdef WIN32
    if(fnamePos == std::string::npos) {
        fnamePos = sFPath_.rfind('\\');
    }
    #endif

    if(fnamePos != std::string::npos) {
        sFName_ = sFPath.substr(fnamePos + 1);
    }
    else {
        sFName_ = sFPath;
    }
}

void SaveFile::load_() {

    iFile_.open(sFPath_, std::ifstream::in);
    if(!iFile_)
        throw ChessException("Failed to load file: " + sFPath_);

    sStream_ << iFile_.rdbuf();
    sData_ = sStream_.str();

    iFile_.close();
    isLoaded_ = true;
}


void SaveFile::print() const {
    #ifdef DEBUG
    std::cout << "\n";
    std::cout << "FILENAME: \n";
    std::cout << sFName_ << "\n";
    std::cout << "\n";
    std::cout << "DATA: \n";
    std::cout << sData_ << "\n";
    std::cout << "\n";
    #endif
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