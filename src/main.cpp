
#include <iostream>
#include <memory>
#include "model/Pawn.h"
#include "./controller/CommandSystem.h"
#include "./command/MoveUnitCommand.h"

int main() {

    unitPtr_t pawn = std::make_shared<Pawn>(Color_t::white, Position(Letter::A, 3));

    CommandSystem commandSystem;

    commandPtr_t move_pawn = std::make_shared<MoveUnitCommand>(pawn, Position(Letter::A, 1));

    commandSystem.executeCommand(move_pawn);

    pawn->print();

    commandSystem.undo();

    pawn->print();

    commandSystem.redo();

    pawn->print();


    std::cout << "Ola chess!" << "\n";
    return 0;
}