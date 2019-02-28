
#include <iostream>
#include <memory>
#include "model/Pawn.h"
#include "./controller/CommandSystem.h"

int main() {
    unitPtr_t pawn = std::make_shared<Pawn>(White, 0, 0);

    CommandSystem commandSystem;

    #ifdef DEBUG
    pawn->print();
    #endif

    std::cout << "Ola chess!" << "\n";
    return 0;
}