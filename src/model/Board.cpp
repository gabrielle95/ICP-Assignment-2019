/*
 * @file Board.cpp
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
#include "../common/Color.h"
#include "Board.h"

Board::Board()
{
    initBoard_();
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
    return nullptr;
}

unitPtr_t Board::At(Position pos)
{
    return At(pos.clm(), pos.row());
}

bool Board::checkMoveValidity(Position toPos)
{
    return positionIsAvailable_(lastAvailableMovesCache_, toPos);
}

void Board::moveUnit(unitPtr_t unit, Position to)
{
    Position unitPos = findUnitPosition(unit);

    // unit is not captured
    if (unitPos.isValid())
    {
        setUnitTo_(unit, to);
        setUnitTo_(nullptr, unitPos);
        if (!unit->movedFromStartingPos())
            unit->setMovedFromStartingPos();
    }
    else if (unitPos == Position(-1, -1))
    {
        //unit is captured
        uncaptureUnit(unit, to);
    }
}

void Board::captureUnit(unitPtr_t unit)
{
    capturedUnits_.push_back(unit);
}

void Board::uncaptureUnit(unitPtr_t unit, Position pos_old)
{
    // mostly for undo
    setUnitTo_(unit, pos_old);
    auto it = std::find(capturedUnits_.begin(), capturedUnits_.end(), unit);
    capturedUnits_.erase(capturedUnits_.begin() + std::distance(capturedUnits_.begin(), it));
}

Position Board::findUnitPosition(unitPtr_t unit)
{
    for (unsigned int c = A; c < board_.size(); c++)
    {

        for (unsigned int r = ONE; r < board_.at(c).size(); r++)
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

std::vector<Position> Board::getPositionsOfPlayersTurn(bool isWhitesTurn)
{
    std::vector<Position> positions;
    color_t color;

    isWhitesTurn ? color = WHITE : color = BLACK;

    for (unsigned int c = A; c < board_.size(); c++)
    {
        for (unsigned int r = ONE; r < board_.at(c).size(); r++)
        {
            unitPtr_t u = board_.at(c).at(r);
            if (u != nullptr)
            {
                if (u->color() == color)
                {
                    positions.emplace_back(c, r);
                }
            }
        }
    }

    return positions;
}

unitPtr_t Board::findActualUnitForShortNotation(unitType_t unitType, color_t color, Position to)
{
    for (auto &col : board_)
    {
        for (auto &rowUnit : col)
        {
            if (rowUnit)
            {
                if (rowUnit->color() == color && rowUnit->type() == unitType)
                {
                    Position fromPos = findUnitPosition(rowUnit);

                    if (unitType == PAWN)
                    {
                        continue;
                    }
                    if (fromPos.isValid() && Rules::checkMoveValidity(rowUnit, fromPos, to))
                    {
                        return rowUnit;
                    }
                }
            }
        }
    }

    /* special case for pawns */

    /* check for movement first */
    for (auto &col : board_)
    {
        for (auto &rowUnit : col)
        {
            if (rowUnit)
            {
                if (rowUnit->color() == color && rowUnit->type() == PAWN)
                {
                    Position fromPos = findUnitPosition(rowUnit);

                    if (fromPos.isValid() && Rules::checkPawnMoving(color, fromPos, to, rowUnit->movedFromStartingPos()))
                    {
                        return rowUnit;
                    }
                }
            }
        }
    }

    /* then check again for capturing */
    for (auto &col : board_)
    {
        for (auto &rowUnit : col)
        {
            if (rowUnit)
            {
                if (rowUnit->color() == color && rowUnit->type() == PAWN)
                {
                    Position fromPos = findUnitPosition(rowUnit);

                    if (fromPos.isValid() && Rules::checkPawnCapturing(color, fromPos, to))
                    {
                        return rowUnit;
                    }
                }
            }
        }
    }

    return nullptr;
}

void Board::resetBoard()
{
    /* clear */
    for (auto &c : board_)
    {
        for (auto &u : c)
        {
            u = nullptr;
        }
    }

    /* set */
    for (auto &u : allUnits_)
    {
        setUnitTo_(u, u->startingPos());
        u->resetFlags();
    }

}

void Board::resetCheck()
{
    for (auto &u : allUnits_)
    {
        u->setInCheck(false);
    }
}

bool Board::isKingInCheck(color_t color)
{
    std::vector<Position> opposingAvailable = getAvailablePositionsForOpposingTeam_(color);
    auto it = std::find_if(allUnits_.begin(), allUnits_.end(), [&](unitPtr_t const &unit) {
        return unit->color() == color && unit->type() == KING;
    });
    unitPtr_t king = (*it);
    Position kingPos = findUnitPosition(king);

    for(auto &pos : opposingAvailable)
    {
        if(pos == kingPos)
        {
            king->setInCheck(true);
            return true;
        }
    }

    king->setInCheck(false);
    return false;
}

bool Board::isKingStalemated(color_t color)
{
    std::vector<Position> opposingAvailable = getAvailablePositionsForOpposingTeam_(color);
    auto it = std::find_if(allUnits_.begin(), allUnits_.end(), [&](unitPtr_t const &unit) {
        return unit->color() == color && unit->type() == KING;
    });
    unitPtr_t king = (*it);

    Position kingPosition = findUnitPosition(king);
    std::vector<Position> availableForKing = getAvailableCellsForUnit(kingPosition);

    std::vector<Position> intersectingPositions = intersectPositionVectors_(opposingAvailable, availableForKing);

    if(availableForKing.empty() && intersectingPositions.empty())
        return false;

    for(auto &inters: intersectingPositions)
    {
        for(auto &pos: availableForKing)
        {
            if(pos != inters)
            {
                return false;
            }
        }
    }

    return true;
}

bool Board::isKingCheckMated(color_t color)
{
    auto it = std::find_if(allUnits_.begin(), allUnits_.end(), [&](unitPtr_t const &unit) {
        return unit->color() == color && unit->type() == KING;
    });
    unitPtr_t king = (*it);

    if(king->isInCheck())
        return true;

    std::vector<Position> opposingAvailable = getAvailablePositionsForOpposingTeam_(color);
    // if king is in not check it cant be checkmated
    if (!king->isInCheck())
        return false;

    Position kingPosition = findUnitPosition(king);
    std::vector<Position> availableForKing = getAvailableCellsForUnit(kingPosition);

    std::vector<Position> intersectingPositions = intersectPositionVectors_(opposingAvailable, availableForKing);

    if(availableForKing.empty() && intersectingPositions.empty())
        return false;

    for(auto &inters: intersectingPositions)
    {
        for(auto &pos: availableForKing)
        {
            if(pos != inters)
            {
                return false;
            }
        }
    }

    return true;
}

std::vector<Position> Board::getAvailablePositionsForOpposingTeam_(color_t color)
{
    std::vector<Position> positions;
    std::vector<Position> available;
    ;

    for (auto &c : board_)
    {
        for (auto &u : c)
        {
            if (!u)
                continue;
            if (u->color() != color)
            {
                available.clear();
                available = getAvailableCellsForUnit(findUnitPosition(u));
                positions.insert(positions.end(), available.begin(), available.end());
            }
        }
    }

    return positions;
}

void Board::setUnitTo_(unitPtr_t unit, Position pos)
{
    board_.at(pos.clm()).at(pos.row()) = unit;
}

std::vector<Position> Board::getAvailableDiagonalPositions_(Position from)
{

    std::vector<Position> available;

    int col, row;

    for (col = from.clm() - 1, row = from.row() + 1; row <= ROW_MAX; col--, row++)
    {
        if (col < COL_MIN)
            break;
        if (board_.at(col).at(row) == nullptr)
        {
            available.push_back(Position(col, row));
            continue;
        }
        if (cachedUnit_->color() != board_.at(col).at(row)->color())
        {
            available.push_back(Position(col, row));
            //board_.at(col).at(row)->setInCheck(true);
        }

        break;
    }
    for (col = from.clm() + 1, row = from.row() + 1; row <= ROW_MAX; col++, row++)
    {
        if (col > COL_MAX)
            break;
        if (board_.at(col).at(row) == nullptr)
        {
            available.push_back(Position(col, row));
            continue;
        }
        if (cachedUnit_->color() != board_.at(col).at(row)->color())
        {
            available.push_back(Position(col, row));
            //board_.at(col).at(row)->setInCheck(true);
        }

        break;
    }
    for (col = from.clm() - 1, row = from.row() - 1; row >= ROW_MIN; col--, row--)
    {
        if (col < COL_MIN)
            break;
        if (board_.at(col).at(row) == nullptr)
        {
            available.push_back(Position(col, row));
            continue;
        }
        if (cachedUnit_->color() != board_.at(col).at(row)->color())
        {
            available.push_back(Position(col, row));
            //board_.at(col).at(row)->setInCheck(true);
        }
        break;
    }
    for (col = from.clm() + 1, row = from.row() - 1; row >= ROW_MIN; col++, row--)
    {
        if (col > COL_MAX)
            break;
        if (board_.at(col).at(row) == nullptr)
        {
            available.push_back(Position(col, row));
            continue;
        }
        if (cachedUnit_->color() != board_.at(col).at(row)->color())
        {
            available.push_back(Position(col, row));
            //board_.at(col).at(row)->setInCheck(true);
        }
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
        {
            available.push_back(Position(from.clm(), row));
            //board_.at(from.clm()).at(row)->setInCheck(true);
        }

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
        {
            available.push_back(Position(from.clm(), row));
            //board_.at(from.clm()).at(row)->setInCheck(true);
        }

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
        {
            available.push_back(Position(col, from.row()));
            //board_.at(col).at(from.row())->setInCheck(true);
        }

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
        {
            available.push_back(Position(col, from.row()));
            //board_.at(col).at(from.row())->setInCheck(true);
        }

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
                    //At(p)->setInCheck(true);
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

void Board::initBoard_()
{

    /******** WHITE ********/

    allUnits_.push_back(std::make_shared<Unit>(WHITE, PAWN, Position(A, TWO)));
    allUnits_.push_back(std::make_shared<Unit>(WHITE, PAWN, Position(B, TWO)));
    allUnits_.push_back(std::make_shared<Unit>(WHITE, PAWN, Position(C, TWO)));
    allUnits_.push_back(std::make_shared<Unit>(WHITE, PAWN, Position(D, TWO)));
    allUnits_.push_back(std::make_shared<Unit>(WHITE, PAWN, Position(E, TWO)));
    allUnits_.push_back(std::make_shared<Unit>(WHITE, PAWN, Position(F, TWO)));
    allUnits_.push_back(std::make_shared<Unit>(WHITE, PAWN, Position(G, TWO)));
    allUnits_.push_back(std::make_shared<Unit>(WHITE, PAWN, Position(H, TWO)));

    allUnits_.push_back(std::make_shared<Unit>(WHITE, ROOK, Position(A, ONE)));
    allUnits_.push_back(std::make_shared<Unit>(WHITE, ROOK, Position(H, ONE)));

    allUnits_.push_back(std::make_shared<Unit>(WHITE, KNIGHT, Position(B, ONE)));
    allUnits_.push_back(std::make_shared<Unit>(WHITE, KNIGHT, Position(G, ONE)));

    allUnits_.push_back(std::make_shared<Unit>(WHITE, BISHOP, Position(C, ONE)));
    allUnits_.push_back(std::make_shared<Unit>(WHITE, BISHOP, Position(F, ONE)));

    allUnits_.push_back(std::make_shared<Unit>(WHITE, QUEEN, Position(D, ONE)));
    allUnits_.push_back(std::make_shared<Unit>(WHITE, KING, Position(E, ONE)));

    /* BLACK */

    allUnits_.push_back(std::make_shared<Unit>(BLACK, PAWN, Position(A, SEVEN)));
    allUnits_.push_back(std::make_shared<Unit>(BLACK, PAWN, Position(B, SEVEN)));
    allUnits_.push_back(std::make_shared<Unit>(BLACK, PAWN, Position(C, SEVEN)));
    allUnits_.push_back(std::make_shared<Unit>(BLACK, PAWN, Position(D, SEVEN)));
    allUnits_.push_back(std::make_shared<Unit>(BLACK, PAWN, Position(E, SEVEN)));
    allUnits_.push_back(std::make_shared<Unit>(BLACK, PAWN, Position(F, SEVEN)));
    allUnits_.push_back(std::make_shared<Unit>(BLACK, PAWN, Position(G, SEVEN)));
    allUnits_.push_back(std::make_shared<Unit>(BLACK, PAWN, Position(H, SEVEN)));

    allUnits_.push_back(std::make_shared<Unit>(BLACK, ROOK, Position(A, EIGHT)));
    allUnits_.push_back(std::make_shared<Unit>(BLACK, ROOK, Position(H, EIGHT)));

    allUnits_.push_back(std::make_shared<Unit>(BLACK, KNIGHT, Position(B, EIGHT)));
    allUnits_.push_back(std::make_shared<Unit>(BLACK, KNIGHT, Position(G, EIGHT)));

    allUnits_.push_back(std::make_shared<Unit>(BLACK, BISHOP, Position(C, EIGHT)));
    allUnits_.push_back(std::make_shared<Unit>(BLACK, BISHOP, Position(F, EIGHT)));

    allUnits_.push_back(std::make_shared<Unit>(BLACK, QUEEN, Position(D, EIGHT)));
    allUnits_.push_back(std::make_shared<Unit>(BLACK, KING, Position(E, EIGHT)));

    resetBoard();
}

std::vector<Position> Board::intersectPositionVectors_(std::vector<Position> a, std::vector<Position> b)
{
    std::vector<Position> intersect;

    std::sort(a.begin(), a.end(), Position::comp);
    std::sort(b.begin(), b.end(), Position::comp);

    std::set_intersection(a.begin(), a.end(),
                          b.begin(), b.end(),
                          std::back_inserter(intersect), Position::comp);

    return intersect;
}
