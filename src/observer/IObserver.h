#pragma once

class IObserver {
    public:
        virtual void onNotify() = 0;
};