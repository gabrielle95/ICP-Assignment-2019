#pragma once

#include <vector>
#include "IObserver.h"

class Subject {
    public:
        Subject();
        void addObserver(IObserver * observer);
        void removeObserver(IObserver * observer);

    protected:
        void notify();

    private:
        std::vector<IObserver *> observers_;
};