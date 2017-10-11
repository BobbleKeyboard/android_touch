//
// Created by kunaldawn on 11/10/17.
//

#include "CharacterDevice.h"
#include <sys/stat.h>

bool android_touch::CharacterDevice::isCharacterDevice(const std::string &path) {
    struct stat statbuf;

    if (stat(path.c_str(), &statbuf) == -1) {
        return false;
    }

    return S_ISCHR(statbuf.st_mode);
}
