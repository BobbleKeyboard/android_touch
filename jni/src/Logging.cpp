/**
 *                  _           _     _   _                   _
 *  __ _ _ __   __| |_ __ ___ (_) __| | | |_ ___  _   _  ___| |__
 * / _` | '_ \ / _` | '__/ _ \| |/ _` | | __/ _ \| | | |/ __| '_ \
 *| (_| | | | | (_| | | | (_) | | (_| | | || (_) | |_| | (__| | | |
 * \__,_|_| |_|\__,_|_|  \___/|_|\__,_|  \__\___/ \__,_|\___|_| |_|
 *
 * Copyright (c) 2017 Kunal Dawn <kunal.dawn@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 */

#include "Logging.h"

android_touch::Logging::Mode android_touch::Logging::LOGGING_MODE = android_touch::Logging::Mode::None;

void android_touch::Logging::setMode(android_touch::Logging::Mode mode) {
    Logging::LOGGING_MODE = mode;
}

void android_touch::Logging::info(std::string tag, std::string message) {
    switch (Logging::LOGGING_MODE) {
        case Mode::Info:
        case Mode::Debug:
        case Mode::Verbose:
            dispatchMessage(tag + " : " + message);
            break;
        default:
            break;
    }
}

void android_touch::Logging::debug(std::string tag, std::string message) {
    switch (Logging::LOGGING_MODE) {
        case Mode::Debug:
        case Mode::Verbose:
            dispatchMessage(tag + " : " + message);
            break;
        default:
            break;
    }
}

void android_touch::Logging::verbose(std::string tag, std::string message) {
    switch (Logging::LOGGING_MODE) {
        case Mode::Verbose:
            dispatchMessage(tag + " : " + message);
            break;
        default:
            break;
    }
}

void android_touch::Logging::dispatchMessage(std::string message) {
#ifdef ANDROID
    __android_log_print(ANDROID_LOG_DEBUG, "android_touch", "%s", message.c_str());
#else
    std::cout << "[android_touch] : " << message << std::endl;
#endif
}
