//
// Created by kunaldawn on 12/10/17.
//

#ifndef PROJECT_TOUCHINPUTDEVICE_H
#define PROJECT_TOUCHINPUTDEVICE_H

#include <string>
#include <memory>
#include <map>

class TouchInputDevice {
protected:
    int mDeviceFileDescriptor;
    int mDeviceScore;
    std::string mDevicePath;

    int mHasMTSlot;
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
    int tracking_id;
    std::map<int, std::shared_ptr> mTouchContacts;

    struct libevdev *evdev = NULL;
};


#endif //PROJECT_TOUCHINPUTDEVICE_H
