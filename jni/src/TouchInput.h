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

#ifndef PROJECT_TOUCHINPUTDEVICE_H
#define PROJECT_TOUCHINPUTDEVICE_H

#include <string>
#include <memory>
#include <map>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <climits>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include "TouchState.h"
#include "../vendor/libevdev/libevdev.h"

namespace android_touch {
    class TouchInput {
    protected:
        static const std::string INPUT_DEVICE_ROOT;
        static constexpr int MT_TOUCH_MAJOR = 0x00000006;
        static constexpr int MT_WIDTH_MAJOR = 0x00000004;
        static constexpr int MAX_SUPPORTED_TOUCH_CONTACTS = 10;

        std::string mInputDeviceFilePath = "";
        int mDeviceFileDescriptor = 0;

        bool mHasKeyButtonTouch = false;
        bool mHasTouchMajor = false;
        bool mHasWidthMajor = false;
        bool mHasPressure = false;
        int mMaxTouchContacts = 0;

        std::vector<std::shared_ptr<TouchState>> mTouchContacts;
        struct libevdev *mInputEventDevice = nullptr;

    public:
        explicit TouchInput(const std::string &inputDevicePath);
        std::string getDevicePath();
        void commit();
        void reset();
        void down(int contact, int x, int y, int pressure);
        void move(int contact, int x, int y, int pressure);
        void up(int contact);
        void delay(int milliseconds);

    public:
        static std::shared_ptr<TouchInput> getNewInstance();

    protected:
        static std::vector<std::string> getFiles(std::string path);
        void writeInputEvent(int type, int code, int value);
        static bool isCharacterDevice(std::string path);
    };
}

#endif //PROJECT_TOUCHINPUTDEVICE_H
