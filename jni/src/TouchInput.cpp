/**
 *                  _           _     _   _                   _
 *  __ _ _ __   __| |_ __ ___ (_) __| | | |_ ___  _   _  ___| |__
 * / _` | '_ \ / _` | '__/ _ \| |/ _` | | __/ _ \| | | |/ __| '_ \
 *| (_| | | | | (_| | | | (_) | | (_| | | || (_) | |_| | (__| | | |
 * \__,_|_| |_|\__,_|_|  \___/|_|\__,_|  \__\___/ \__,_|\___|_| |_|
 *
 * Copyright (c) 2017 Kunal Dawn <kunal.dawn@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 */

#include <thread>
#include "TouchInput.h"
#include "Logging.h"

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

    mHasKeyButtonTouch = libevdev_has_event_code(mInputEventDevice, EV_KEY, BTN_TOUCH) == 1;
    mHasTouchMajor = libevdev_has_event_code(mInputEventDevice, EV_ABS, ABS_MT_TOUCH_MAJOR) == 1;
    mHasWidthMajor = libevdev_has_event_code(mInputEventDevice, EV_ABS, ABS_MT_WIDTH_MAJOR) == 1;
    mHasPressure = libevdev_has_event_code(mInputEventDevice, EV_ABS, ABS_MT_PRESSURE) == 1;
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

std::string android_touch::TouchInput::getDevicePath() {
    return mInputDeviceFilePath;
}

void android_touch::TouchInput::commit() {
    Logging::info("TouchInput", "commit");
    writeInputEvent(EV_SYN, SYN_REPORT, 0);
}

void android_touch::TouchInput::reset() {
    Logging::info("TouchInput", "reset");
    bool needCommit = false;
    for (const auto &touchContact : mTouchContacts) {
        if (touchContact->getState() != TouchState::State::Disabled) {
            needCommit = true;
            touchContact->setState(TouchState::State::Disabled);
        }
    }

    if (needCommit) {
        commit();
    }
}

void android_touch::TouchInput::down(int contact, int x, int y, int pressure) {
    Logging::info("TouchInput", "down : " + std::to_string(contact) + " : " + std::to_string(x) + " : " + std::to_string(y) + " : " + std::to_string(pressure));
    if (contact >= mMaxTouchContacts) {
        return;
    }

    if (mTouchContacts[contact]->getState() != TouchState::State::Disabled) {
        reset();
    }

    mTouchContacts[contact]->setState(TouchState::State::WentDown);

    writeInputEvent(EV_ABS, ABS_MT_SLOT, contact);
    writeInputEvent(EV_ABS, ABS_MT_TRACKING_ID, mTouchContacts[contact]->getTrackingID());

    if (mHasKeyButtonTouch) {
        writeInputEvent(EV_KEY, BTN_TOUCH, 1);
    }

    if (mHasTouchMajor) {
        writeInputEvent(EV_ABS, ABS_MT_TOUCH_MAJOR, MT_TOUCH_MAJOR);
    }

    if (mHasWidthMajor) {
        writeInputEvent(EV_ABS, ABS_MT_WIDTH_MAJOR, MT_WIDTH_MAJOR);
    }

    if (mHasPressure) {
        writeInputEvent(EV_ABS, ABS_MT_PRESSURE, pressure);
    }

    writeInputEvent(EV_ABS, ABS_MT_POSITION_X, x);
    writeInputEvent(EV_ABS, ABS_MT_POSITION_Y, y);
}

void android_touch::TouchInput::move(int contact, int x, int y, int pressure) {
    Logging::info("TouchInput", "move : " + std::to_string(contact) + " : " + std::to_string(x) + " : " + std::to_string(y) + " : " + std::to_string(pressure));
    if (contact >= mMaxTouchContacts) {
        return;
    }

    if (mTouchContacts[contact]->getState() == TouchState::State::Disabled) {
        return;
    }

    writeInputEvent(EV_ABS, ABS_MT_SLOT, contact);

    if (mHasTouchMajor) {
        writeInputEvent(EV_ABS, ABS_MT_TOUCH_MAJOR, MT_TOUCH_MAJOR);
    }

    if (mHasWidthMajor) {
        writeInputEvent(EV_ABS, ABS_MT_WIDTH_MAJOR, MT_WIDTH_MAJOR);
    }

    if (mHasPressure) {
        writeInputEvent(EV_ABS, ABS_MT_PRESSURE, pressure);
    }

    writeInputEvent(EV_ABS, ABS_MT_POSITION_X, x);
    writeInputEvent(EV_ABS, ABS_MT_POSITION_Y, y);
}

void android_touch::TouchInput::up(int contact) {
    Logging::info("TouchInput", "up : " + std::to_string(contact));
    if (contact >= mMaxTouchContacts) {
        return;
    }

    if (mTouchContacts[contact]->getState() == TouchState::State::Disabled) {
        return;
    }

    mTouchContacts[contact]->setState(TouchState::State::Disabled);

    writeInputEvent(EV_ABS, ABS_MT_SLOT, contact);
    writeInputEvent(EV_ABS, ABS_MT_TRACKING_ID, -1);

    if (mHasKeyButtonTouch) {
        writeInputEvent(EV_KEY, BTN_TOUCH, 0);
    }
}

void android_touch::TouchInput::writeInputEvent(int type, int code, int value) {
    Logging::verbose("TouchInput", "writeInputEvent : " + std::to_string(type)  + " : " + std::to_string(code) + " : " + std::to_string(value));
    timespec timeSpec{};
    clock_gettime(CLOCK_MONOTONIC, &timeSpec);
    struct input_event inputEvent = {
            {timeSpec.tv_sec, timeSpec.tv_nsec / 1000},
            (uint16_t)type,
            (uint16_t)code,
            value
    };
    write(mDeviceFileDescriptor, &inputEvent, sizeof(input_event));
}

bool android_touch::TouchInput::isCharacterDevice(std::string path) {
    struct stat statusBuffer{};

    if (stat(path.c_str(), &statusBuffer) == -1) {
        return false;
    }

    return S_ISCHR(statusBuffer.st_mode);
}

std::vector<std::string> android_touch::TouchInput::getFiles(std::string path) {
    std::vector<std::string> list;
    DIR *dir = opendir(path.c_str());
    struct dirent *entry = readdir(dir);

    while (entry != nullptr) {
        if (entry->d_type != DT_DIR) {
            std::string fileName = std::string(entry->d_name);
            list.push_back(fileName);
        }
        entry = readdir(dir);
    }
    closedir(dir);

    return list;
}

void android_touch::TouchInput::delay(int milliseconds) {
    Logging::info("TouchInput", "delay : " + std::to_string(milliseconds));
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
