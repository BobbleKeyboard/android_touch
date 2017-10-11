//
// Created by kunaldawn on 11/10/17.
//

#ifndef PROJECT_TOUCHPOINT_H
#define PROJECT_TOUCHPOINT_H

namespace android_touch {
    class TouchPoint {
    private:
        int mX;
        int mY;
        int mPressure;

    public:
        TouchPoint() : mX(0), mY(0), mPressure(0) {
        }

        TouchPoint(int x, int y, int pressure) : mX(x), mY(y), mPressure(pressure) {
        }

        void setX(int x) {
            mX = x;
        }

        void setY(int y) {
            mY = y;
        }

        void setPressure(int pressuer) {
            mPressure = pressuer;
        }

        int getX() {
            return mX;
        }

        int getY() {
            return mY;
        }

        int getPressure() {
            return mPressure;
        }
    };
}

#endif //PROJECT_TOUCHPOINT_H
