//
// Created by kunaldawn on 11/10/17.
//

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
