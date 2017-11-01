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

#ifndef PROJECT_MULTITOUCHCONTACT_H
#define PROJECT_MULTITOUCHCONTACT_H

#include <memory>

namespace android_touch {
    class TouchState {
    public:
        enum class State {
            WentUp,
            WentDown,
            Moved,
            Disabled
        };

    protected:
        State mState;
        int mTrackingID;

    public:
        /**
         * Default constructor of this class
         */
        TouchState();

        /**
         * Set the state
         *
         * @param state State
         */
        void setState(State state);

        /**
         * Get the state
         *
         * @return State
         */
        State getState();

        /**
         * Set the tracking ID
         *
         * @param trackingID Tracking ID
         */
        void setTrackingID(int trackingID);

        /**
         * Get the tracking ID
         *
         * @return Tracking ID
         */
        int getTrackingID();
    };
}

#endif //PROJECT_MULTITOUCHCONTACT_H
