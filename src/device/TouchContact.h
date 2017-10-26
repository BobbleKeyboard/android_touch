//
// Created by kunaldawn on 11/10/17.
//

#ifndef PROJECT_MULTITOUCHCONTACT_H
#define PROJECT_MULTITOUCHCONTACT_H

#include "TouchPoint.h"

namespace android_touch {
    class TouchContact {
    protected:
        bool mIsEnabled;
        int mTrackingID;
        TouchPoint mTouchPoint;

    public:
        TouchContact();
    };
}

#endif //PROJECT_MULTITOUCHCONTACT_H
