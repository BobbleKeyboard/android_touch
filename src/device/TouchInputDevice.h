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
#include <unistd.h>
#include "TouchContact.h"
#include "../utils/FileUtils.h"
#include "CharacterInputDevice.h"

namespace android_touch {
    class TouchInputDevice : public CharacterInputDevice {
    protected:
        static constexpr int MT_TOUCH_MAJOR = 0x00000006;
        static constexpr int MT_WIDTH_MAJOR = 0x00000004;
        static constexpr int MAX_SUPPORTED_TOUCH_CONTACTS = 10;

        std::string mInputDeviceFilePath = "";
        int mDeviceFileDescriptor = 0;

        bool mHasMultiTouchSlot = false;
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
        int mTrackingID = 0;

        std::vector<std::shared_ptr<TouchContact>> mTouchContacts;
        struct libevdev *mInputEventDevice = nullptr;

    public:
        TouchInputDevice(const std::string &inputDevicePath);

        static std::shared_ptr<TouchInputDevice> getNewInstance();

        void commit() {
            if (mHasMultiTouchSlot) {
                commitTypeB();
            } else {
                commitTypeA();
            }
        }

        void reset() {
            if (mHasMultiTouchSlot) {
                resetTypeB();
            } else {
                resetTypeA();
            }
        }

        void down(int contact, std::shared_ptr<TouchPoint> touchPoint) {
            if (mHasMultiTouchSlot) {
                downTypeB(contact, touchPoint);
            } else {
                downTypeA(contact, touchPoint);
            }
        }

        void move(std::shared_ptr<TouchPoint> touchPoint) {

        }

        void up(std::shared_ptr<TouchPoint> touchPoint) {

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

        void commitTypeA() {
            bool needSync = false;
            for (const auto &touchContact : mTouchContacts) {
                switch (touchContact->getState()) {
                    case TouchContact::State::Disabled:
                        break;
                    case TouchContact::State::WentDown:
                        needSync = true;

                        if (mHasTrackingID) {
                            writeInputEvent(EV_ABS, ABS_MT_TRACKING_ID, touchContact->getTrackingID());
                        }

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
                            writeInputEvent(EV_ABS, ABS_MT_PRESSURE, touchContact->getTouchPoint()->getPressure());
                        }

                        writeInputEvent(EV_ABS, ABS_MT_POSITION_X, touchContact->getTouchPoint()->getX());
                        writeInputEvent(EV_ABS, ABS_MT_POSITION_Y, touchContact->getTouchPoint()->getY());
                        writeInputEvent(EV_SYN, SYN_MT_REPORT, 0);

                        touchContact->setState(TouchContact::State::Moved);
                        break;
                    case TouchContact::State::Moved:
                        needSync = true;

                        if (mHasTrackingID) {
                            writeInputEvent(EV_ABS, ABS_MT_TRACKING_ID, touchContact->getTrackingID());
                        }

                        if (mHasTouchMajor) {
                            writeInputEvent(EV_ABS, ABS_MT_TOUCH_MAJOR, MT_TOUCH_MAJOR);
                        }

                        if (mHasWidthMajor) {
                            writeInputEvent(EV_ABS, ABS_MT_WIDTH_MAJOR, MT_WIDTH_MAJOR);
                        }

                        if (mHasPressure) {
                            writeInputEvent(EV_ABS, ABS_MT_PRESSURE, touchContact->getTouchPoint()->getPressure());
                        }

                        writeInputEvent(EV_ABS, ABS_MT_POSITION_X, touchContact->getTouchPoint()->getX());
                        writeInputEvent(EV_ABS, ABS_MT_POSITION_Y, touchContact->getTouchPoint()->getY());
                        writeInputEvent(EV_SYN, SYN_MT_REPORT, 0);
                        break;
                    case TouchContact::State::WentUp:
                        needSync = true;

                        if (mHasTrackingID) {
                            writeInputEvent(EV_ABS, ABS_MT_TRACKING_ID, touchContact->getTrackingID());
                        }

                        if (mHasKeyButtonTouch) {
                            writeInputEvent(EV_KEY, BTN_TOUCH, 0);
                        }

                        writeInputEvent(EV_SYN, SYN_MT_REPORT, 0);
                        touchContact->setState(TouchContact::State::Disabled);
                        break;
                }
            }

            if (needSync) {
                writeInputEvent(EV_SYN, SYN_REPORT, 0);
            }
        };

        void commitTypeB() {
            writeInputEvent(EV_SYN, SYN_REPORT, 0);
        };

        void resetTypeA() {
            for (const auto &touchContact : mTouchContacts) {
                switch (touchContact->getState()) {
                    case TouchContact::State::Disabled:
                        break;
                    case TouchContact::State::WentDown:
                        touchContact->setState(TouchContact::State::WentUp);
                        break;
                    case TouchContact::State::Moved:
                        touchContact->setState(TouchContact::State::WentUp);
                        break;
                    case TouchContact::State::WentUp:
                        break;
                }
            }

            commitTypeA();
        }

        void resetTypeB() {
            bool needCommit = false;
            for (const auto &touchContact : mTouchContacts) {
                if (touchContact->getState() != TouchContact::State::Disabled) {
                    needCommit = true;
                    touchContact->setState(TouchContact::State::Disabled);
                }
            }

            if (needCommit) {
                commitTypeB();
            }
        }

        void downTypeA(int contact, std::shared_ptr<TouchPoint> touchPoint) {

        }

        void downTypeB(int contact, std::shared_ptr<TouchPoint> touchPoint) {

        }
    };
}

#endif //PROJECT_TOUCHINPUTDEVICE_H
