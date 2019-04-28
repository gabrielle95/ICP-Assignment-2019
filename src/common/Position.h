#pragma once

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
    Position() : clm_(A), row_(ONE) {}

    Position(letter_t clm, rowPos_t row)
        : clm_(clm), row_(row) {}

    Position(int clm, int row)
        : clm_((letter_t)clm), row_((rowPos_t)row) {}

    rowPos_t row() const
    {
        return row_;
    }

    letter_t clm() const
    {
        return clm_;
    }

    void set(letter_t clm, rowPos_t row)
    {
        clm_ = clm;
        row_ = row;
    }

    bool isValid() const
    {
        return clm_ >= 0 && row_ >= 0 && clm_ <= 7 && row_ <= 7;
    }

    std::string to_str()
    {
        std::string lb = "(";
        std::string rb = ")";
        std::string separator = (",");
        return lb + std::to_string(clm_) + separator + std::to_string(row_) + rb;
    }

    bool operator==(const Position &p) const
    {
        return clm_ == p.clm() && row_ == p.row();
    }

    bool operator!=(const Position &p) const
    {
        return clm_ != p.clm() || row_ != p.row();
    }

    static bool comp(const Position &a, const Position &b)
    {
        return a.clm() < b.clm() && a.row() < b.row();
    }

  private:
    letter_t clm_;
    rowPos_t row_;
};
