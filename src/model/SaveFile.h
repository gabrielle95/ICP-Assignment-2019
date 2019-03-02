#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Unit.h"

class SaveFile {
    public:
        SaveFile(std::string sFPath);

    private:

        bool load_();
        bool write_();

        unitType_t unitTypeFrom_(char c);
        char charFrom_(unitType_t unitType);


        std::ifstream iFile_;
        std::ofstream oFile_;
        std::string sName_;
        std::string sFPath_;
        std::string sData_;
        std::stringstream sStream_;
};