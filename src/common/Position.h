/*
 * @file Position.h
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
#pragma once

/**
 * @brief The enum with letters representing columns in chess
 *
 */
enum letter_t
{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H
};

/**
 * @brief The enum with rows representing the row numbers in chess
 *
 */
enum rowPos_t
{
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT
};

class Position
{
  public:
    /**
     * @brief Construct a new Position object with default values
     *
     */
    Position() : clm_(A), row_(ONE) {}

    /**
     * @brief Construct a new Position object
     *
     * @param clm The position column
     * @param row The position row
     */
    Position(letter_t clm, rowPos_t row)
        : clm_(clm), row_(row) {}

    /**
     * @brief Construct a new Position object
     *
     * @param clm The position column
     * @param row The position row
     */
    Position(int clm, int row)
        : clm_((letter_t)clm), row_((rowPos_t)row) {}

    /**
     * @brief Getter for the row
     *
     * @return rowPos_t The row in the position
     */
    rowPos_t row() const
    {
        return row_;
    }

    /**
     * @brief Getter for the column
     *
     * @return letter_t The column of the position
     */
    letter_t clm() const
    {
        return clm_;
    }

    /**
     * @brief Sets new values to a position instance
     *
     * @param clm The new column
     * @param row The new row
     */
    void set(letter_t clm, rowPos_t row)
    {
        clm_ = clm;
        row_ = row;
    }

    /**
     * @brief Checks whether the position is in bounds
     *
     * @return true The position is in bounds and valid
     * @return false The position is out of bounds and invalid
     */
    bool isValid() const
    {
        return clm_ >= 0 && row_ >= 0 && clm_ <= 7 && row_ <= 7;
    }

    /**
     * @brief Overloads the == operator on Position instances
     *
     * @param p The position being compared to
     * @return true The Positions are equal
     * @return false The Positions are not equal
     */
    bool operator==(const Position &p) const
    {
        return clm_ == p.clm() && row_ == p.row();
    }

    /**
     * @brief Overloads the != operator on Position instances
     *
     * @param p The position being compared to
     * @return true The Positions are not equal
     * @return false The Positions are equal
     */
    bool operator!=(const Position &p) const
    {
        return clm_ != p.clm() || row_ != p.row();
    }

    /**
     * @brief A function that compares tow positions
     *
     * @param a The lhs Position
     * @param b The rhs Position
     * @return true The lhs is smaller than rhs
     * @return false The lhs is greater then rhs
     */
    static bool comp(const Position &a, const Position &b)
    {
        return a.clm() < b.clm() && a.row() < b.row();
    }

  private:
    letter_t clm_;
    rowPos_t row_;
};
