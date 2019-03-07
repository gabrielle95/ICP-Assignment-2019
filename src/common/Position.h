enum letter_t {
    A, B, C, D, E, F, G, H
};

enum rowPos_t {
    ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT
};

class Position {
    public:

        Position() : clm_(A), row_(ONE) {}

        Position (letter_t clm, rowPos_t row)
        : clm_(clm), row_(row) {}

        rowPos_t row() const {
            return row_;
        }

        letter_t clm() const {
            return clm_;
        }

        void set(letter_t clm, rowPos_t row) {
            clm_ = clm;
            row_ = row;
        }

    private:
        letter_t clm_;
        rowPos_t row_;
};