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
        /**
         *
         */
        TouchPoint();

        /**
         *
         * @param x
         * @param y
         */
        TouchPoint(int x, int y);

        /**
         *
         * @param x
         * @param y
         * @param pressure
         */
        TouchPoint(int x, int y, int pressure);

        /**
         *
         * @param x
         */
        void setX(int x);

        /**
         *
         * @param y
         */
        void setY(int y);

        /**
         *
         * @param pressuer
         */
        void setPressure(int pressuer);

        /**
         *
         * @return
         */
        int getX();

        /**
         *
         * @return
         */
        int getY();

        /**
         *
         * @return
         */
        int getPressure();
    };
}

#endif //PROJECT_TOUCHPOINT_H
