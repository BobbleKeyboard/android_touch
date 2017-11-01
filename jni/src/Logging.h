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

#ifndef PROJECT_LOGGING_H
#define PROJECT_LOGGING_H

#include <iostream>

#ifdef ANDROID
#include <android/log.h>
#endif

namespace android_touch {
    class Logging {
    public:
        enum class Mode {
            None,
            Info,
            Debug,
            Verbose
        };

    private:
        static Mode LOGGING_MODE;

    public:
        static void setMode(Mode mode);
        static void info(std::string tag, std::string message);
        static void debug(std::string tag, std::string message);;
        static void verbose(std::string tag, std::string message);;

    private:
        static void dispatchMessage(std::string message);;
    };
}

#endif //PROJECT_LOGGING_H
