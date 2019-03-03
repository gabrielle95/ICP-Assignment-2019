#pragma once

#include <memory>

using subjectPtr_t = std::shared_ptr<class ISubject>;

class IObserver {
    public:
        virtual void onNotify(subjectPtr_t subject) = 0;
};
