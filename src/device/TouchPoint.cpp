//
// Created by kunaldawn on 11/10/17.
//

#include "TouchPoint.h"

android_touch::TouchPoint::TouchPoint() : mX(0), mY(0), mPressure(0) {
}

android_touch::TouchPoint::TouchPoint(int x, int y) : mX(x), mY(y), mPressure(0) {
}

android_touch::TouchPoint::TouchPoint(int x, int y, int pressure) : mX(x), mY(y), mPressure(pressure) {
}

void android_touch::TouchPoint::setX(int x) {
    mX = x;
}

void android_touch::TouchPoint::setY(int y) {
    mY = y;
}

void android_touch::TouchPoint::setPressure(int pressuer) {
    mPressure = pressuer;
}

int android_touch::TouchPoint::getX() {
    return mX;
}

int android_touch::TouchPoint::getY() {
    return mY;
}

int android_touch::TouchPoint::getPressure() {
    return mPressure;
}
