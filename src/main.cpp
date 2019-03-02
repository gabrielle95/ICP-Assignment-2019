#include <iostream>
#include <memory>
#include <string>
#include "model/Pawn.h"
#include "./controller/CommandSystem.h"
#include "./command/MoveUnitCommand.h"
#include "./common/ChessException.h"
#include "./controller/SaveSystem.h"

int main() {

    // Undo Redo
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

    try {
        throw ChessException("Unknown Unit Type");
    }
    catch (ChessException& e) {
        std::cerr << e.what() << "\n";
    }

    // Save system
    SaveSystem saveSystem;
    saveSystem.load("./examples/save01");
    if(saveSystem.getOpenedSave()) saveSystem.getOpenedSave()->print();

    return 0;
}