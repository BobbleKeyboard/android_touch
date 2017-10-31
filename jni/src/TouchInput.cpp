//
// Created by kunaldawn on 12/10/17.
//

#include "TouchInput.h"

const std::string android_touch::TouchInput::INPUT_DEVICE_ROOT = "/dev/input/";

std::shared_ptr<android_touch::TouchInput> android_touch::TouchInput::getNewInstance() {
    std::vector<std::string> inputDeviceFileNames = getFiles(INPUT_DEVICE_ROOT);

    int maxInputDeviceScore = -1;
    std::string maxInputDevicePath;
    for (const auto &inputDeviceFileName : inputDeviceFileNames) {
        const auto inputDevicePath = INPUT_DEVICE_ROOT + inputDeviceFileName;
        int currentInputDeviceScore = 1000;
        int inputDeviceFileDescriptor;
        struct libevdev *inputEventDevice = NULL;

        if (!isCharacterDevice(inputDevicePath)) {
            libevdev_free(inputEventDevice);
            continue;
        }

        inputDeviceFileDescriptor = open(inputDevicePath.c_str(), O_RDWR);
        if (inputDeviceFileDescriptor < 0) {
            libevdev_free(inputEventDevice);
            continue;
        }

        if (libevdev_new_from_fd(inputDeviceFileDescriptor, &inputEventDevice)) {
            libevdev_free(inputEventDevice);
            continue;
        }

        if (!libevdev_has_event_code(inputEventDevice, EV_ABS, ABS_MT_POSITION_X)) {
            libevdev_free(inputEventDevice);
            continue;
        }

        if (!libevdev_has_event_code(inputEventDevice, EV_ABS, ABS_MT_SLOT)) {
            libevdev_free(inputEventDevice);
            continue;
        }

        if (libevdev_has_event_code(inputEventDevice, EV_ABS, ABS_MT_TOOL_TYPE)) {
            int toolMinimum = libevdev_get_abs_minimum(inputEventDevice, ABS_MT_TOOL_TYPE);
            int toolMaximum = libevdev_get_abs_maximum(inputEventDevice, ABS_MT_TOOL_TYPE);

            if (toolMinimum > MT_TOOL_FINGER || toolMaximum < MT_TOOL_FINGER) {
                libevdev_free(inputEventDevice);
                continue;
            }

            currentInputDeviceScore -= toolMaximum - MT_TOOL_FINGER;
        }

        std::string inputDeviceName = libevdev_get_name(inputEventDevice);
        if (inputDeviceName.find("key") != std::string::npos) {
            currentInputDeviceScore -= 1;
        }

        if (libevdev_has_property(inputEventDevice, INPUT_PROP_DIRECT)) {
            currentInputDeviceScore += 1000;
        }

        if (maxInputDeviceScore < currentInputDeviceScore) {
            maxInputDeviceScore = currentInputDeviceScore;
            maxInputDevicePath = inputDevicePath;
        }

        libevdev_free(inputEventDevice);
    }

    if (maxInputDeviceScore > 0) {
        return std::make_shared<TouchInput>(maxInputDevicePath);
    }

    return nullptr;
}

android_touch::TouchInput::TouchInput(const std::string &inputDevicePath) {
    mInputDeviceFilePath = inputDevicePath;

    mDeviceFileDescriptor = open(mInputDeviceFilePath.c_str(), O_RDWR);
    if (mDeviceFileDescriptor < 0) {
        libevdev_free(mInputEventDevice);
        return;
    }

    if (libevdev_new_from_fd(mDeviceFileDescriptor, &mInputEventDevice)) {
        libevdev_free(mInputEventDevice);
        return;
    }

    mHasTrackingID = libevdev_has_event_code(mInputEventDevice, EV_ABS, ABS_MT_TRACKING_ID) == 1;
    mHasKeyButtonTouch = libevdev_has_event_code(mInputEventDevice, EV_KEY, BTN_TOUCH) == 1;
    mHasTouchMajor = libevdev_has_event_code(mInputEventDevice, EV_ABS, ABS_MT_TOUCH_MAJOR) == 1;
    mHasWidthMajor = libevdev_has_event_code(mInputEventDevice, EV_ABS, ABS_MT_WIDTH_MAJOR) == 1;
    mHasPressure = libevdev_has_event_code(mInputEventDevice, EV_ABS, ABS_MT_PRESSURE) == 1;

    if (mHasPressure) {
        mMinPressure = libevdev_get_abs_minimum(mInputEventDevice, ABS_MT_PRESSURE);
        mMaxPressure = libevdev_get_abs_maximum(mInputEventDevice, ABS_MT_PRESSURE);
    }

    mMaxX = libevdev_get_abs_maximum(mInputEventDevice, ABS_MT_POSITION_X);
    mMaxY = libevdev_get_abs_maximum(mInputEventDevice, ABS_MT_POSITION_Y);

    if (mHasTrackingID) {
        mMaxTrackingID = libevdev_get_abs_maximum(mInputEventDevice, ABS_MT_TRACKING_ID);
    } else {
        mMaxTrackingID = INT_MAX;
    }

    mMaxTouchContacts = libevdev_get_abs_maximum(mInputEventDevice, ABS_MT_SLOT) + 1;

    if (mMaxTouchContacts > MAX_SUPPORTED_TOUCH_CONTACTS) {
        mMaxTouchContacts = MAX_SUPPORTED_TOUCH_CONTACTS;
    }

    for (auto index = 1; index <= mMaxTouchContacts; index++) {
        auto contact = std::make_shared<TouchState>();
        contact->setTrackingID(index);
        contact->setState(TouchState::State::Disabled);
        mTouchContacts.push_back(contact);
    }
}
