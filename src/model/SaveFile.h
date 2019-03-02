#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Unit.h"

class SaveSystem;

class SaveFile {
    public:
        SaveFile(std::string sFPath);

        static char charFrom_(int coord);
        static int coordFrom_(char c);

        void print() const;

        bool isLoaded() const {
            return isLoaded_;
        }

    private:

        friend SaveSystem;

        void load_();
        void validateData_();

        bool write_();

        static unitType_t unitTypeFrom_(char c);
        static char charFrom_(unitType_t unitType);

        static letter_t letterCoordFrom_(char letter);
        static char letterCharFrom_(letter_t letter);

        std::ifstream iFile_;
        std::ofstream oFile_;
        std::string sFName_;
        std::string sFPath_;
        std::string sData_;
        std::stringstream sStream_;

        bool isLoaded_;
};