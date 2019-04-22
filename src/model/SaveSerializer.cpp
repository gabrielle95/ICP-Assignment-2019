#include "SaveSerializer.h"
#include "../common/ChessException.h"
#include "../command/MoveUnitCommand.h"
#include <cctype>
#include <cstdlib>

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
    serialized += std::to_string(command->new_pos().row() + 1);

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

    commandVector_t deserializedLine;
    for (auto line : lines)
    {
        deserializedLine.clear();
        deserializedLine = deserializeLine_(line, board);
        commands.insert(commands.end(), deserializedLine.begin(), deserializedLine.end());
    }

     return commands;
}

commandVector_t SaveSerializer::deserializeLine_(std::string line, boardPtr_t board)
{

    commandVector_t commands;
    commandPtr_t command;

    unsigned int pos = 0;
    unsigned int lookAhead = 1;
    const char period = '.';

    std::string whiteDelimiter(" ");

    //expect line numbering
    if (line.at(lookAhead) != period)
    {
        lookAhead++;
        if (line.at(lookAhead) != period)
        {
            lookAhead++;
            if (line.at(lookAhead != period))
            {
                throw ChessException("ERROR: Incorrect or non-existent line numbering");
            }
        }
    }

    lookAhead++;
    if (line.at(lookAhead) != ' ')
    {
        throw ChessException("No whitespace after line nubering.");
    }

    lookAhead += 2;
    //pos = lookAhead - 1; //pos on space

    //size_t i = pos;
    std::string subst;

    //white substr command
    /*while ((i = line.find(whiteDelimiter)) != std::string::npos)
    {
        subst = line.substr(pos, i);
        //lines.push_back(line);
        //s.erase(0, pos + delimiter.length());
    }*/

    //finds and erases line numbering and space
    pos = line.find(whiteDelimiter);
    pos++;
    line.erase(0, pos);

    //gets the white substring until space
    pos = line.find(whiteDelimiter);
    subst = line.substr(0, pos);
    pos++;

    if (subst.empty())
    {
        throw ChessException("ERROR: Did not find space delimiter between white and black draw.");
    }

    command = deserializeCommand_(subst, board, WHITE);
    commands.emplace_back(command);

    subst.clear();

    // the rest is black command
    subst = line.substr(pos);

    command = deserializeCommand_(subst, board, BLACK);
    commands.emplace_back(command);

    return commands;
}

commandPtr_t SaveSerializer::deserializeCommand_(std::string subst, boardPtr_t board, color_t drawColor)
{
    commandPtr_t command;

    char c;

    //default
    unitType_t unitType = PAWN;

    int col = -1;
    int row = -1;

    Position to(-1, -1);
    Position from(-1, -1);

    unitPtr_t actualUnit; // will be found on the board

    bool isLongNotationOn = false;
    bool checkedForLongNotation = false;

    bool isCapturing = false;

    bool acquiredFromPosition = false;
    bool acquiredToPosition = false;

    for (unsigned int pos = 0; pos < subst.size(); pos++)
    {

        if (!checkedForLongNotation && Position(col, row).isValid())
        {
            unitPtr_t unitAtParsedPos = board->At(Position(col, row));
            if (unitAtParsedPos)
            {
                if (unitAtParsedPos->color() == drawColor)
                {
                    // long notation is on
                    // because we acquired a position of unit, that is going
                    // to move FROM this position (it is the same color as the draw color
                    // so it cannot be an enemy unit that is being captured
                    isLongNotationOn = true;
                    from = Position(col, row);
                }
                checkedForLongNotation = true;
            }
        }

        c = subst.at(pos);

        if (isCharacterUnitType_(c))
        {
            unitType = unitTypeFrom_(c);
        }

        if (isCharacterColumnCoord_(c))
        {
            col = letterCoordFrom_(c);
        }

        if (isCharacterRowCoord_(c))
        {
            row = atoi(&c) - 1;
        }

        if (isCharacterSpecialEvent_(c))
        {
            switch (c)
            {
            case 'x':
                isCapturing = true;
                break;
                //TODO
            default:
                break;
            }
        }

        /*if (isLongNotationOn && !acquiredFromPosition)
        {
            if (Position(col, row).isValid())
            {
                from = Position(col, row);
                acquiredFromPosition = true;
            }
        }*/

        if ((!isLongNotationOn && !acquiredToPosition) || (isLongNotationOn && acquiredFromPosition && !acquiredToPosition))
        {
            if (Position(col, row).isValid())
            {
                to = Position(col, row);
                acquiredToPosition = true;
            }
        }
    }

    if (!from.isValid())
    {
        //need to parse hinting columns or rows according to pdf

        actualUnit = board->findActualUnitForShortNotation(unitType, drawColor, to);
    }
    else {
        actualUnit = board->At(from);
    }

    if (!actualUnit)
        throw ChessException("Error: An illegal move was detected inside the save file.");

    command = std::make_shared<MoveUnitCommand>(board, actualUnit, to);
    // execute this command, to simulate the recorded game
    command->execute();
    return command;
}

unitType_t SaveSerializer::unitTypeFrom_(char c)
{
    switch (c)
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
    case 'p': // ?
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

bool SaveSerializer::isCharacterUnitType_(char c)
{
    return (c >= 'A' && c <= 'Z');
}

bool SaveSerializer::isCharacterColumnCoord_(char c)
{
    return (c >= 'a' && c <= 'h');
}

bool SaveSerializer::isCharacterRowCoord_(char c)
{
    return (c >= '1' && c <= '8');
}

bool SaveSerializer::isCharacterSpecialEvent_(char c)
{
    return (c == 'x' || c == '+' || c == '#');
}
