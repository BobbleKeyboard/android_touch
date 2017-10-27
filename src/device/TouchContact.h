//
// Created by kunaldawn on 11/10/17.
//

#ifndef PROJECT_MULTITOUCHCONTACT_H
#define PROJECT_MULTITOUCHCONTACT_H

#include <bits/shared_ptr.h>
#include "TouchPoint.h"

namespace android_touch {
    class TouchContact {
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
        std::shared_ptr<TouchPoint> mTouchPoint;

    public:
        TouchContact();

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

        void setTouchPoint(std::shared_ptr<TouchPoint> touchPoint) {
            mTouchPoint = touchPoint;
        }

        std::shared_ptr<TouchPoint> getTouchPoint() {
            return mTouchPoint;
        }
    };
}

#endif //PROJECT_MULTITOUCHCONTACT_H
