//
// Created by kunaldawn on 11/10/17.
//

#ifndef PROJECT_MULTITOUCHCONTACT_H
#define PROJECT_MULTITOUCHCONTACT_H

#include "TouchPoint.h"

namespace android_touch {
    class MultiTouchContact {
    protected:
        bool mIsEnabled;
        int mTrackingID;
        TouchPoint mTouchPoint;

    public:
        MultiTouchContact() : mIsEnabled(false), mTrackingID(0) {
        }


    };
}

#endif //PROJECT_MULTITOUCHCONTACT_H
