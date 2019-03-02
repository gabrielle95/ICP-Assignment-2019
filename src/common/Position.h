enum letter_t {
    A = 1, B, C, D, E, F, G, H
};

class Position {
    public:

        Position() : clm_(0), row_(0) {}

        Position (int clm, int row)
        : clm_(clm), row_(row) {}

        int row() const {
            return row_;
        }

        int clm() const {
            return clm_;
        }

        void set(int clm, int row) {
            clm_ = clm;
            row_ = row;
        }

    private:
        int clm_;
        int row_;
};