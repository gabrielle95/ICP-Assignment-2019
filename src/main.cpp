#include <iostream>
#include <memory>
#include <string>
#include "model/Pawn.h"
#include "./controller/CommandSystem.h"
#include "./command/MoveUnitCommand.h"
#include "./common/ChessException.h"
#include "./model/SaveFile.h"

int main() {

    unitPtr_t pawn = std::make_shared<Pawn>(WHITE, Position(A, 3));

    CommandSystem commandSystem;

    commandPtr_t move_pawn = std::make_shared<MoveUnitCommand>(pawn, Position(A, 1));

    commandSystem.executeCommand(move_pawn);

    pawn->print();

    commandSystem.undo();

    pawn->print();

    commandSystem.redo();

    pawn->print();

    std::cout << "Ola chess!" << "\n";

    // Exception demo
    char c = 'g';
    try {
        throw ChessException("Unknown Unit Type: " + std::string(&c));
    }
    catch (ChessException& e) {
        std::cerr << e.what() << "\n";
    }

    // Save file

    // SaveFile save("save.txt");

    return 0;
}