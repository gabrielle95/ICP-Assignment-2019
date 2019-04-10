#include "../common/Color.h"
#include "Board.h"

Board::Board()
{

    /******** WHITE ********/

    board_.at(A).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(A, TWO));
    board_.at(B).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(B, TWO));
    board_.at(C).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(C, TWO));
    board_.at(D).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(D, TWO));
    board_.at(E).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(E, TWO));
    board_.at(F).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(F, TWO));
    board_.at(G).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(G, TWO));
    board_.at(H).at(TWO) = std::make_shared<Unit>(WHITE, PAWN, Position(H, TWO));

    board_.at(A).at(ONE) = std::make_shared<Unit>(WHITE, ROOK, Position(A, ONE));
    board_.at(H).at(ONE) = std::make_shared<Unit>(WHITE, ROOK, Position(H, ONE));

    board_.at(B).at(ONE) = std::make_shared<Unit>(WHITE, KNIGHT, Position(B, ONE));
    board_.at(G).at(ONE) = std::make_shared<Unit>(WHITE, KNIGHT, Position(G, ONE));

    board_.at(C).at(ONE) = std::make_shared<Unit>(WHITE, BISHOP, Position(C, ONE));
    board_.at(F).at(ONE) = std::make_shared<Unit>(WHITE, BISHOP, Position(F, ONE));

    board_.at(D).at(ONE) = std::make_shared<Unit>(WHITE, QUEEN, Position(D, ONE));
    board_.at(E).at(ONE) = std::make_shared<Unit>(WHITE, KING, Position(E, ONE));

    /******** BLACK ********/

    board_.at(A).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(A, SEVEN));
    board_.at(B).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(B, SEVEN));
    board_.at(C).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(C, SEVEN));
    board_.at(D).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(D, SEVEN));
    board_.at(E).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(E, SEVEN));
    board_.at(F).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(F, SEVEN));
    board_.at(G).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(G, SEVEN));
    board_.at(H).at(SEVEN) = std::make_shared<Unit>(BLACK, PAWN, Position(H, SEVEN));

    board_.at(A).at(EIGHT) = std::make_shared<Unit>(BLACK, ROOK, Position(A, EIGHT));
    board_.at(H).at(EIGHT) = std::make_shared<Unit>(BLACK, ROOK, Position(H, EIGHT));

    board_.at(B).at(EIGHT) = std::make_shared<Unit>(BLACK, KNIGHT, Position(B, EIGHT));
    board_.at(G).at(EIGHT) = std::make_shared<Unit>(BLACK, KNIGHT, Position(G, EIGHT));

    board_.at(C).at(EIGHT) = std::make_shared<Unit>(BLACK, BISHOP, Position(C, EIGHT));
    board_.at(F).at(EIGHT) = std::make_shared<Unit>(BLACK, BISHOP, Position(F, EIGHT));

    board_.at(D).at(EIGHT) = std::make_shared<Unit>(BLACK, QUEEN, Position(D, EIGHT));
    board_.at(E).at(EIGHT) = std::make_shared<Unit>(BLACK, KING, Position(E, EIGHT));
}

unitPtr_t Board::At(letter_t clm, rowPos_t row)
{

    try
    {
        return board_.at(clm).at(row);
    }
    catch (std::out_of_range &e)
    {
        std::cerr << e.what() << "\n";
        std::cerr << "Error: Accessed out of range coords.\n";
    }
}

unitPtr_t Board::At(Position pos)
{
    return At(pos.clm(), pos.row());
}

void Board::print()
{
    for (int c = A; c < board_.size(); c++)
    {

        for (int r = ONE; r < board_.at(c).size(); r++)
        {
            if (board_.at(c).at(r))
                board_.at(c).at(r)->print();
        }
    }
}

bool Board::checkMoveValidity(unitPtr_t unit, Position fromPos, Position toPos)
{
    return positionIsAvailable_(lastAvailableMovesCache_, toPos);
}

void Board::moveUnit(unitPtr_t unit, Position to)
{
    Position unitPos = findUnitPosition(unit);

    // unit is not captured
    if (unitPos.isValid())
    {
        /*if (At(to) != nullptr) //redo this
        {
            captureUnit(At(to));
        }*/
        setUnitTo_(unit, to);
        setUnitTo_(nullptr, unitPos);
        if (!unit->movedFromStartingPos())
            unit->setMovedFromStartingPos();
    }
}

void Board::captureUnit(unitPtr_t unit)
{
    capturedUnits_.push_back(unit);
}

void Board::uncaptureUnit(unitPtr_t unit, Position pos_old)
{
    setUnitTo_(unit, pos_old);
    auto it = std::find(capturedUnits_.begin(), capturedUnits_.end(), unit);
    capturedUnits_.erase(capturedUnits_.begin() + std::distance(capturedUnits_.begin(), it));
}

Position Board::findUnitPosition(unitPtr_t unit)
{
    for (int c = A; c < board_.size(); c++)
    {

        for (int r = ONE; r < board_.at(c).size(); r++)
        {
            if (board_.at(c).at(r) == unit)
            {
                return Position(c, r);
            }
        }
    }
    return Position(-1, -1);
}

std::vector<Position> Board::getAvailableCellsForUnit(Position from)
{

    lastAvailableMovesCache_.clear();
    cachedUnit_ = nullptr;

    cachedUnit_ = At(from);

    if (cachedUnit_ != nullptr)
    {
        unitType_t unitType = cachedUnit_->type();
        std::vector<Position> rows;
        std::vector<Position> cols;
        std::vector<Position> diagonals;
        std::vector<Position> positions;

        if (unitType == ROOK)
        {
            rows = getAvailableRowPositions_(from);
            cols = getAvailableColPositions_(from);
            std::copy(rows.begin(), rows.end(), std::back_inserter(lastAvailableMovesCache_));
            std::copy(cols.begin(), cols.end(), std::back_inserter(lastAvailableMovesCache_));
        }
        else if (unitType == BISHOP)
        {
            diagonals = getAvailableDiagonalPositions_(from);
            std::copy(diagonals.begin(), diagonals.end(), std::back_inserter(lastAvailableMovesCache_));
        }
        else if (unitType == QUEEN)
        {
            rows = getAvailableRowPositions_(from);
            cols = getAvailableColPositions_(from);
            diagonals = getAvailableDiagonalPositions_(from);

            std::copy(rows.begin(), rows.end(), std::back_inserter(lastAvailableMovesCache_));
            std::copy(cols.begin(), cols.end(), std::back_inserter(lastAvailableMovesCache_));
            std::copy(diagonals.begin(), diagonals.end(), std::back_inserter(lastAvailableMovesCache_));
        }
        else if (unitType == KING)
        {
            positions = getFirstAvailableFromAllDirs_(from);
            std::copy(positions.begin(), positions.end(), std::back_inserter(lastAvailableMovesCache_));
        }
        else if (unitType == KNIGHT)
        {
            positions = getAvailableKnightPositions_(from);
            std::copy(positions.begin(), positions.end(), std::back_inserter(lastAvailableMovesCache_));
        }
        else if (unitType == PAWN)
        {
            positions = getAvailablePawnPositions_(from);
            std::copy(positions.begin(), positions.end(), std::back_inserter(lastAvailableMovesCache_));
        }
    }
    return lastAvailableMovesCache_;
}

void Board::setUnitTo_(unitPtr_t unit, Position pos)
{
    board_.at(pos.clm()).at(pos.row()) = unit;
}

std::vector<Position> Board::getAvailableDiagonalPositions_(Position from)
{

    std::vector<Position> available;

    int col, row;

    for (col = from.clm() - 1, row = from.row() + 1; col >= COL_MIN, row <= ROW_MAX; col--, row++)
    {
        if (col < COL_MIN)
            break;
        if (board_.at(col).at(row) == nullptr)
        {
            available.push_back(Position(col, row));
            continue;
        }
        if (cachedUnit_->color() != board_.at(col).at(row)->color())
            available.push_back(Position(col, row));
        break;
    }
    for (col = from.clm() + 1, row = from.row() + 1; col <= COL_MAX, row <= ROW_MAX; col++, row++)
    {
        if (col > COL_MAX)
            break;
        if (board_.at(col).at(row) == nullptr)
        {
            available.push_back(Position(col, row));
            continue;
        }
        if (cachedUnit_->color() != board_.at(col).at(row)->color())
            available.push_back(Position(col, row));
        break;
    }
    for (col = from.clm() - 1, row = from.row() - 1; col >= COL_MIN, row >= ROW_MIN; col--, row--)
    {
        if (col < COL_MIN)
            break;
        if (board_.at(col).at(row) == nullptr)
        {
            available.push_back(Position(col, row));
            continue;
        }
        if (cachedUnit_->color() != board_.at(col).at(row)->color())
            available.push_back(Position(col, row));
        break;
    }
    for (col = from.clm() + 1, row = from.row() - 1; col <= COL_MAX, row >= ROW_MIN; col++, row--)
    {
        if (col > COL_MAX)
            break;
        if (board_.at(col).at(row) == nullptr)
        {
            available.push_back(Position(col, row));
            continue;
        }
        if (cachedUnit_->color() != board_.at(col).at(row)->color())
            available.push_back(Position(col, row));
        break;
    }
    return available;
}

std::vector<Position> Board::getAvailableRowPositions_(Position from)
{
    int row;
    std::vector<Position> available;

    for (row = from.row() - 1; row >= ROW_MIN; row--)
    {
        if (board_.at(from.clm()).at(row) == nullptr)
        {
            available.push_back(Position(from.clm(), row));
            continue;
        }
        if (cachedUnit_->color() != board_.at(from.clm()).at(row)->color())
            available.push_back(Position(from.clm(), row));
        break;
    }
    for (row = from.row() + 1; row <= ROW_MAX; row++)
    {
        if (board_.at(from.clm()).at(row) == nullptr)
        {
            available.push_back(Position(from.clm(), row));
            continue;
        }
        if (cachedUnit_->color() != board_.at(from.clm()).at(row)->color())
            available.push_back(Position(from.clm(), row));
        break;
    }
    return available;
}

std::vector<Position> Board::getAvailableColPositions_(Position from)
{
    int col;
    std::vector<Position> available;

    for (col = from.clm() - 1; col >= COL_MIN; col--)
    {
        if (board_.at(col).at(from.row()) == nullptr)
        {
            available.push_back(Position(col, from.row()));
            continue;
        }
        if (cachedUnit_->color() != board_.at(col).at(from.row())->color())
            available.push_back(Position(col, from.row()));
        break;
    }
    for (col = from.clm() + 1; col <= ROW_MAX; col++)
    {
        if (board_.at(col).at(from.row()) == nullptr)
        {
            available.push_back(Position(col, from.row()));
            continue;
        }
        if (cachedUnit_->color() != board_.at(col).at(from.row())->color())
            available.push_back(Position(col, from.row()));
        break;
    }
    return available;
}

std::vector<Position> Board::getFirstAvailableFromAllDirs_(Position from)
{
    std::vector<Position> maybe;

    maybe.emplace_back(from.clm(), from.row() + 1);
    maybe.emplace_back(from.clm(), from.row() - 1);

    maybe.emplace_back(from.clm() + 1, from.row());
    maybe.emplace_back(from.clm() - 1, from.row());

    maybe.emplace_back(from.clm() + 1, from.row() + 1);
    maybe.emplace_back(from.clm() + 1, from.row() - 1);
    maybe.emplace_back(from.clm() - 1, from.row() + 1);
    maybe.emplace_back(from.clm() - 1, from.row() - 1);

    return validatePossiblyAvailablePositions_(maybe, cachedUnit_);
}

std::vector<Position> Board::getAvailableKnightPositions_(Position from)
{

    std::vector<Position> maybe;

    int row = from.row();
    int col = from.clm();

    maybe.emplace_back(col + 1, row + 2);
    maybe.emplace_back(col + 1, row - 2);
    maybe.emplace_back(col - 1, row + 2);
    maybe.emplace_back(col - 1, row - 2);

    maybe.emplace_back(col + 2, row + 1);
    maybe.emplace_back(col + 2, row - 1);
    maybe.emplace_back(col - 2, row + 1);
    maybe.emplace_back(col - 2, row - 1);

    return validatePossiblyAvailablePositions_(maybe, cachedUnit_);
}

std::vector<Position> Board::getAvailablePawnPositions_(Position from)
{
    std::vector<Position> maybe;

    std::vector<Position> maybeCapturingPositions;

    std::vector<Position> available;

    unitPtr_t unit = At(from);

    if (unit->color() == BLACK)
    {
        if (!unit->movedFromStartingPos())
        {
            maybe.emplace_back(from.clm(), from.row() - 2);
        }
        maybe.emplace_back(from.clm(), from.row() - 1);
        maybeCapturingPositions.emplace_back(from.clm() - 1, from.row() - 1);
        maybeCapturingPositions.emplace_back(from.clm() + 1, from.row() - 1);
    }
    else
    { // WHITE
        if (!unit->movedFromStartingPos())
        {
            maybe.emplace_back(from.clm(), from.row() + 2);
        }
        maybe.emplace_back(from.clm(), from.row() + 1);
        maybeCapturingPositions.emplace_back(from.clm() - 1, from.row() + 1);
        maybeCapturingPositions.emplace_back(from.clm() + 1, from.row() + 1);
    }

    for (auto &p : maybe)
    {
        if (p.isValid())
        {
            if (At(p) == nullptr)
            {
                available.push_back(p);
            }
        }
    }

    for (auto &p : maybeCapturingPositions)
    {
        if (p.isValid())
        {
            if (At(p) != nullptr)
            {
                if (unit->color() != At(p)->color())
                {
                    available.push_back(p);
                }
            }
        }
    }

    return available;
}

bool Board::positionIsAvailable_(std::vector<Position> positions, Position pos)
{
    for (auto &p : positions)
    {
        if (p == pos)
            return true;
    };
    return false;
}

std::vector<Position> Board::validatePossiblyAvailablePositions_(std::vector<Position> possible, unitPtr_t forUnit)
{
    std::vector<Position> available;

    for (auto &p : possible)
    {
        if (p.isValid())
        {
            if (At(p) != nullptr)
            {
                if (forUnit->color() != At(p)->color())
                {
                    available.push_back(p);
                }
            }
            else
            {
                available.push_back(p);
            }
        }
    }
    return available;
}