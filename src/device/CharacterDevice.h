//
// Created by kunaldawn on 11/10/17.
//

#ifndef PROJECT_CHARACTERDEVICE_H
#define PROJECT_CHARACTERDEVICE_H

#include "Device.h"

namespace android_touch {
    /**
     *
     */
    class CharacterDevice : public Device {
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
