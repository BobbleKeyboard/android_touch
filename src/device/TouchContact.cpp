//
// Created by kunaldawn on 11/10/17.
//

#include "TouchContact.h"

android_touch::TouchContact::TouchContact() : mState(State::Disabled), mTrackingID(0), mTouchPoint(std::make_shared<TouchPoint>()) {
}
