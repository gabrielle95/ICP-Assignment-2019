#include "SaveSerializer.h"
#include "../common/ChessException.h"

std::string SaveSerializer::serializeOutput_(commandVector_t outputCommands)
{
    std::vector<std::string> serializedLines;
    std::string line;

    int lineNumber = 1;

    // 2 commands per line - white followed by black
    int commandLineCounter = 0;

    for (auto &c : outputCommands)
    {

        // add line number
        if (commandLineCounter == 0)
        {
            line += std::to_string(lineNumber) + ". ";
        }

        // serialize one command
        line += serializeCommand_(c);

        //if black command, add newline
        if (commandLineCounter == 1)
        {
            line += "\n";
        }
        else
        {
            line += " ";
        }

        commandLineCounter++;

        if (commandLineCounter > 1)
        {
            serializedLines.push_back(line);
            line.clear();
            lineNumber++;
            commandLineCounter = 0;
        }
    }

    std::string serializedOutput;

    for (auto s : serializedLines)
    {
        serializedOutput += s;
    }

    return serializedOutput;
}

std::string SaveSerializer::serializeCommand_(commandPtr_t command)
{
    std::string serialized;

    // unit letter
    serialized += strFrom_(command->movingUnit()->type());

    // captured x ?
    if (command->capturedUnit())
    {
        serialized += "x";
    }

    // clm to
    serialized += letterStrFrom_(command->new_pos().clm());

    // row to
    serialized += std::to_string(command->new_pos().row());

    return serialized;
}

commandVector_t SaveSerializer::deserializeInput_(std::string input, boardPtr_t board)
{

    commandVector_t commands;

    std::vector<std::string> lines;

    std::string s(input);
    std::string delimiter("\n");
    size_t pos = 0;

    std::string line;

    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        line = s.substr(0, pos);
        lines.push_back(line);
        s.erase(0, pos + delimiter.length());
    }

    for (auto line : lines)
    {
        commands.push_back(deserializeLine_(line, board));
    }

    return commands;
}

commandPtr_t SaveSerializer::deserializeLine_(std::string line, boardPtr_t board)
{

    commandPtr_t command;

    for (auto i : line)
    {
        ;
    }

    return command;
}

unitType_t SaveSerializer::unitTypeFrom_(std::string c)
{
    switch (c.at(0))
    {
    case 'K':
        return unitType_t::KING;
    case 'D':
        return unitType_t::QUEEN;
    case 'V':
        return unitType_t::ROOK;
    case 'S':
        return unitType_t::BISHOP;
    case 'J':
        return unitType_t::KNIGHT;
    case 'p':
        return unitType_t::PAWN;
    default:
        throw ChessException("Unknown Unit Type");
    }
}

std::string SaveSerializer::strFrom_(unitType_t unitType)
{
    switch (unitType)
    {
    case unitType_t::KING:
        return std::string("K");
    case unitType_t::QUEEN:
        return std::string("D");
    case unitType_t::ROOK:
        return std::string("V");
    case unitType_t::BISHOP:
        return std::string("S");
    case unitType_t::KNIGHT:
        return std::string("J");
    case unitType_t::PAWN:
        return std::string("");
    default:
        throw ChessException("Unit Type supplied not part of enum unitType_t.");
    }
}

letter_t SaveSerializer::letterCoordFrom_(char letter)
{
    switch (letter)
    {
    case 'a':
        return letter_t::A;
    case 'b':
        return letter_t::B;
    case 'c':
        return letter_t::C;
    case 'd':
        return letter_t::D;
    case 'e':
        return letter_t::E;
    case 'f':
        return letter_t::F;
    case 'g':
        return letter_t::G;
    case 'h':
        return letter_t::H;
    default:
        throw ChessException("No letter coordinate.");
    }
}

std::string SaveSerializer::letterStrFrom_(letter_t letter)
{
    switch (letter)
    {
    case letter_t::A:
        return std::string("a");
    case letter_t::B:
        return std::string("b");
    case letter_t::C:
        return std::string("c");
    case letter_t::D:
        return std::string("d");
    case letter_t::E:
        return std::string("e");
    case letter_t::F:
        return std::string("f");
    case letter_t::G:
        return std::string("g");
    case letter_t::H:
        return std::string("h");
    default:
        throw ChessException("Letter supplied not part of enum letter_t.");
    }
}
