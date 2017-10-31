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

        bool mHasTrackingID = false;
        bool mHasKeyButtonTouch = false;
        bool mHasTouchMajor = false;
        bool mHasWidthMajor = false;
        bool mHasPressure = false;

        int mMinPressure = 0;
        int mMaxPressure = 0;
        int mMaxX = 0;
        int mMaxY = 0;
        int mMaxTouchContacts = 0;
        int mMaxTrackingID = 0;

        static std::vector<std::string> getFiles(std::string path) {
            std::vector<std::string> list;
            DIR *dir = opendir(path.c_str());
            struct dirent *entry = readdir(dir);

            while (entry != NULL) {
                if (entry->d_type != DT_DIR) {
                    std::string fileName = std::string(entry->d_name);
                    list.push_back(fileName);
                }
                entry = readdir(dir);
            }
            closedir(dir);

            return list;
        }

        static bool isCharacterDevice(std::string path) {
            struct stat statusBuffer{};

            if (stat(path.c_str(), &statusBuffer) == -1) {
                return false;
            }

            return S_ISCHR(statusBuffer.st_mode);
        }

        std::vector<std::shared_ptr<TouchState>> mTouchContacts;
        struct libevdev *mInputEventDevice = nullptr;

    public:
        TouchInput(const std::string &inputDevicePath);

        static std::shared_ptr<TouchInput> getNewInstance();

        void commit() {
            writeInputEvent(EV_SYN, SYN_REPORT, 0);
        }

        void reset() {
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

        void down(int contact, int x, int y, int pressure) {
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

        void move(int contact, int x, int y, int pressure) {
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

        void up(int contact) {
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

    protected:
        void writeInputEvent(int type, int code, int value) {
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
    };
}

#endif //PROJECT_TOUCHINPUTDEVICE_H
