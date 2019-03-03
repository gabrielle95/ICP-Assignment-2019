#include <iostream>
#include <memory>
#include <string>
#include "model/Pawn.h"
#include "./controller/CommandSystem.h"
#include "./command/MoveUnitCommand.h"
#include "./common/ChessException.h"
#include "./controller/SaveSystem.h"

int main() {

    commandSystemPtr_t commandSystem = std::make_shared<CommandSystem>();
    saveSystemPtr_t saveSystem = std::make_shared<SaveSystem>();

    saveSystem->registerObserver(commandSystem);
    commandSystem->registerObserver(saveSystem);

    commandSystem->notifyObservers();
    saveSystem->notifyObservers();
    // Undo Redo
    /*unitPtr_t pawn = std::make_shared<Pawn>(WHITE, Position(A, 3));

    commandPtr_t move_pawn = std::make_shared<MoveUnitCommand>(pawn, Position(A, 1));

    commandSystem->executeCommand(move_pawn);

    pawn->print();

    commandSystem->undo();

    pawn->print();

    commandSystem->redo();

    pawn->print();

    std::cout << "Ola chess!" << "\n";

    // Exception demo

    try {
        throw ChessException("Unknown Unit Type");
    }
    catch (ChessException& e) {
        std::cerr << e.what() << "\n";
    }*/

    // Save system
    saveSystem->load("./examples/save01");
    if(saveSystem->getOpenedSave()) saveSystem->getOpenedSave()->print();
    saveSystem->saveAs("./examples/save02");

    return 0;
}