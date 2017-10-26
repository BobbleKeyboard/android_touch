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
#include <climits>
#include "TouchContact.h"
#include "../utils/FileUtils.h"
#include "CharacterInputDevice.h"

namespace android_touch {
    class TouchInputDevice : public CharacterInputDevice {
    protected:
        static constexpr int MAX_SUPPORTED_TOUCH_CONTACTS = 10;
        std::string mInputDeviceFilePath = "";
        int mDeviceFileDescriptor = 0;

        bool mHasMultiTouchSlot = false;
        bool mHasTrackingID = false;
        bool mHasKeyButtonTouch = false;
        bool mHasTouchMajor = false;
        bool mHasTouchWidthMajor = false;
        bool mHasPressure = false;

        int mMinPressure = 0;
        int mMaxPressure = 0;
        int mMaxX = 0;
        int mMaxY = 0;
        int mMaxTouchContacts = 0;
        int mMaxTrackingID = 0;
        int mTrackingID = 0;

        std::map<int, std::shared_ptr<TouchContact>> mTouchContacts;
        struct libevdev *mInputEventDevice = NULL;

    public:
        TouchInputDevice(const std::string &inputDevicePath);

        static std::shared_ptr<TouchInputDevice> getNewInstance();
    };
}

#endif //PROJECT_TOUCHINPUTDEVICE_H
