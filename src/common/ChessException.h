#include <iostream>
#include <string>

class ChessException : public std::runtime_error {
    public:
        ChessException(const std::string& error) : std::runtime_error(error){}
};