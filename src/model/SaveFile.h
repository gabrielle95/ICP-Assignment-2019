#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Unit.h"
#include "../controller/CommandSystem.h"

enum specialEvent_t {
    CAPTURE,
    CHECK,
    MATE
};

class SaveSystem;

class SaveFile {
    public:
        SaveFile(std::string sFPath);

        void print() const;

        bool isLoaded() const {
            return isLoaded_;
        }

    private:

        friend SaveSystem;

        void load_();

        void write_();

        void writeAs_(std::string fileName);

        void serializeOutput_(commandVector_t outputCommands);
        void serializeLine_(commandPtr_t command);

        commandVector_t deserializeInput_();
        commandPtr_t deserializeLine_(std::string line);

        static unitType_t unitTypeFrom_(char c);
        static char charFrom_(unitType_t unitType);

        static letter_t letterCoordFrom_(char letter);
        static char letterCharFrom_(letter_t letter);

        void assignFileName_();

        std::ifstream iFile_;
        std::ofstream oFile_;
        std::string sFName_;
        std::string sFPath_;
        std::string sIData_;
        std::string sOData_;
        std::stringstream sStream_;

        commandVector_t generatedCommands_;

        bool isLoaded_;
};