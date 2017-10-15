//
// Created by kunaldawn on 12/10/17.
//

#ifndef PROJECT_TOUCHINPUTDEVICE_H
#define PROJECT_TOUCHINPUTDEVICE_H

#include <string>
#include <memory>
#include <map>
#include "TouchContact.h"

namespace android_touch {
    class TouchInputDevice {
    protected:
        int mDeviceFileDescriptor;
        int mDeviceScore;
        std::string mDevicePath;

        int mHasMultiTouchSlot;
        int mHasTrackingID;
        int mHasKeyButtonTouch;
        int mHasTouchMajor;
        int mHasTouchWidthMajor;
        int mHasPressure;
        int mMinPressure;
        int mMaxPressure;
        int mMaxX;
        int mMaxY;
        int mMaxContacts;
        int mMaxTrackingID;
        int mTrackingID;
        std::map<int, std::shared_ptr<TouchContact>> mTouchContacts;

        struct libevdev *mEventDevice = NULL;
    };
}

#endif //PROJECT_TOUCHINPUTDEVICE_H
