//
// Created by kunaldawn on 11/10/17.
//

#ifndef PROJECT_DEVICEUTILS_H
#define PROJECT_DEVICEUTILS_H

#include <iostream>

namespace android_touch {
    class DeviceUtils {
    public:
        static bool isCharacterDevice(const std::string &file_path);
    };
}


#endif //PROJECT_DEVICEUTILS_H
