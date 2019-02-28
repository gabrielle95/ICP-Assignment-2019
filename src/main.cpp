
#include <iostream>
#include <memory>
#include "model/Pawn.h"
#include "./controller/CommandSystem.h"
#include "./command/MoveUnitCommand.h"

int main() {

    unitPtr_t pawn = std::make_shared<Pawn>(White, 0, 0);
    CommandSystem commandSystem;

    commandPtr_t move_pawn = std::make_shared<MoveUnitCommand>(pawn, 1, 1);
    commandSystem.executeCommand(move_pawn);

    #ifdef DEBUG
    pawn->print();
    #endif

    commandSystem.undo();

    #ifdef DEBUG
    pawn->print();
    #endif

    commandSystem.redo();

    #ifdef DEBUG
    pawn->print();
    #endif

    std::cout << "Ola chess!" << "\n";
    return 0;
}