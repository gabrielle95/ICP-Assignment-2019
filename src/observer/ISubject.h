#pragma once

#include <vector>
#include <algorithm>
#include "IObserver.h"

using observerPtr_t = std::shared_ptr<IObserver>;
using observerVector_t = std::vector<observerPtr_t>;

class ISubject {
    public:

        virtual void registerObserver(observerPtr_t observer) {
            observers_.push_back(observer);
        }

        virtual void unregisterObserver(observerPtr_t observer) {
            auto it = std::find(observers_.begin(), observers_.end(), observer);

            if(it != observers_.end()) {
                observers_.erase(it);
            }
        }

        virtual void printNotification() = 0;

    protected:

        virtual void notifyObservers() = 0;
        observerVector_t observers_;
};