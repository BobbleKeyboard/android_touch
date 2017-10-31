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

        void setState(State state) {
            mState = state;
        }

        State getState() {
            return mState;
        }

        void setTrackingID(int trackingID) {
            mTrackingID = trackingID;
        }

        int getTrackingID() {
            return mTrackingID;
        }
    };
}

#endif //PROJECT_MULTITOUCHCONTACT_H
