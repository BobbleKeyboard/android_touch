//
// Created by kunaldawn on 11/10/17.
//

#ifndef PROJECT_CHARACTERDEVICE_H
#define PROJECT_CHARACTERDEVICE_H

#include "InputDevice.h"

namespace android_touch {
    /**
     *
     */
    class CharacterInputDevice : public InputDevice {
    protected:
        static constexpr int STAT_ERROR = -1;
    public:
        /**
         *
         * @param path
         * @return
         */
        static bool isCharacterDevice(const std::string &path);
    };
}

#endif //PROJECT_CHARACTERDEVICE_H
