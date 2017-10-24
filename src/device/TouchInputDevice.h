//
// Created by kunaldawn on 12/10/17.
//

#ifndef PROJECT_TOUCHINPUTDEVICE_H
#define PROJECT_TOUCHINPUTDEVICE_H

#include <string>
#include <memory>
#include <map>
#include <vector>
#include <iostream>
#include <libevdev-1.0/libevdev/libevdev.h>
#include <fcntl.h>
#include "TouchContact.h"
#include "../utils/FileUtils.h"
#include "CharacterInputDevice.h"

namespace android_touch {
    class TouchInputDevice : public CharacterInputDevice {
    protected:
        std::string mInputDeviceFilePath;
        int mDeviceFileDescriptor;
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

    public:
        TouchInputDevice(std::string inputDevicePath) {
            mInputDeviceFilePath = inputDevicePath;
        }

        static std::shared_ptr<TouchInputDevice> getNewInstance();
    };
}

#endif //PROJECT_TOUCHINPUTDEVICE_H
