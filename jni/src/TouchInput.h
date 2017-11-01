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
        /**
         * Default constructor of this class.
         *
         * @param inputDevicePath Path of the valid input device
         */
        explicit TouchInput(const std::string &inputDevicePath);

        /**
         * Get the device path for this touch device
         * @return Device path
         */
        std::string getDevicePath();

        /**
         * Send a commit event
         */
        void commit();

        /**
         * Send a reset event
         */
        void reset();

        /**
         * Send touch down event
         *
         * @param contact Contact ID
         * @param x X coordinate
         * @param y Y coordinate
         * @param pressure Pressure
         */
        void down(int contact, int x, int y, int pressure);

        /**
         * Send touch move event
         *
         * @param contact Contact ID
         * @param x X coordinate
         * @param y Y coordinate
         * @param pressure Pressure
         */
        void move(int contact, int x, int y, int pressure);

        /**
         * Send touch up event
         *
         * @param contact Contact ID
         */
        void up(int contact);

        /**
         * Wait for specified time
         *
         * @param milliseconds Time in milliseconds
         */
        void delay(int milliseconds);

    public:
        /**
         * Get the most suitable touch input device by scanning all input device
         *
         * @return TouchInput instance if found, else nullpointer
         */
        static std::shared_ptr<TouchInput> getNewInstance();

    protected:
        /**
         * Get list of all files in the specified directory
         *
         * @param path Root directory
         * @return list of all files in that directory
         */
        static std::vector<std::string> getFiles(std::string path);

        /**
         * Send a raw event to the device
         *
         * @param type Event type
         * @param code Event code
         * @param value Event value
         */
        void writeInputEvent(int type, int code, int value);

        /**
         * Check if given file is a character device file
         *
         * @param path path of the file
         * @return Boolean true if specified file is character device, false otherwise
         */
        static bool isCharacterDevice(std::string path);
    };
}

#endif //PROJECT_TOUCHINPUTDEVICE_H
