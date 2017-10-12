//
// Created by kunaldawn on 11/10/17.
//

#include "CharacterInputDevice.h"
#include <sys/stat.h>

bool android_touch::CharacterInputDevice::isCharacterDevice(const std::string &path) {
    struct stat statusBuffer{};

    if (stat(path.c_str(), &statusBuffer) == STAT_ERROR) {
        return false;
    }

    return S_ISCHR(statusBuffer.st_mode);
}
