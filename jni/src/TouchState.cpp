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

#include "TouchState.h"

android_touch::TouchState::TouchState() {
    mState = State::Disabled;
}

void android_touch::TouchState::setState(android_touch::TouchState::State state) {
    mState = state;
}

android_touch::TouchState::State android_touch::TouchState::getState() {
    return mState;
}

void android_touch::TouchState::setTrackingID(int trackingID) {
    mTrackingID = trackingID;
}

int android_touch::TouchState::getTrackingID() {
    return mTrackingID;
}
