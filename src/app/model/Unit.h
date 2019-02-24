#pragma once

enum Color {
    White = 0,
    Black = 1
};

class Unit {
    public:
        virtual ~Unit();

        virtual void moveTo(int x, int y) {
            if(this->_canMoveTo(x, y)) {
                this->x_ = x;
                this->y_ = y;
                //notify
            }
        };

        // used when redo or undo is called to skip checking
        //if the unit can move somwhere, as it was checked once already
        virtual void moveTo(int x, int y, bool skipCheck) {
            if(!skipCheck) this->moveTo(x,y);
            else {
                this->x_ = x;
                this->y_ = y;
            }
        }

        virtual int x() {
            return this->x_;
        }

        virtual int y() {
            return this->y_;
        }

        virtual Color color() {
            return this->color_;
        }

    private:

        // will be implemented for each type of unit
        virtual bool _canMoveTo(int x, int y) = 0;

        int x_, y_;
        Color color_;
};