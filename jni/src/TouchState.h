//
// Created by kunaldawn on 11/10/17.
//

#ifndef PROJECT_MULTITOUCHCONTACT_H
#define PROJECT_MULTITOUCHCONTACT_H

#include <memory>

namespace android_touch {
    class TouchState {
    public:
        enum class State {
            WentUp,
            WentDown,
            Moved,
            Disabled
        };

    protected:
        State mState;
        int mTrackingID;

    public:
        TouchState();
        void setState(State state);
        State getState();
        void setTrackingID(int trackingID);
        int getTrackingID();
    };
}

#endif //PROJECT_MULTITOUCHCONTACT_H
