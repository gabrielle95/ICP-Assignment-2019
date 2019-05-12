/*
 * @file main.cpp
 *
 * Project name:
 * Chess 2019
 *
 * Description:
 * http://www.fit.vutbr.cz/study/courses/ICP/public/ICP-PRJ-zadani.html.cs
 *
 * Team:
 * @author Gabriela Pacakova (xpacak01)
 * @author Adam Lanicek (xlanic04)
 */
#include <iostream>
#include <memory>

#include "../../controller/CommandSystem.h"
#include "../../command/MoveUnitCommand.h"
#include "../../common/ChessException.h"
#include "../../controller/SaveSystem.h"
#include "../../model/Board.h"

int main()
{

    commandSystemPtr_t commandSystem = std::make_shared<CommandSystem>();
    saveSystemPtr_t saveSystem = std::make_shared<SaveSystem>();
    boardPtr_t board = std::make_shared<Board>();
    std::cout << "Running cli \n";
    return 0;
}