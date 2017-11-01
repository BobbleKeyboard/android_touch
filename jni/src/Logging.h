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
        /**
         * Set logging mode, by default mode is set to None
         *
         * @param mode Logging mode to use
         */
        static void setMode(Mode mode);

        /**
         * Log information message
         *
         * @param tag Tag name
         * @param message Message
         */
        static void info(std::string tag, std::string message);

        /**
         * Log debug message
         *
         * @param tag Tag name
         * @param message Message
         */
        static void debug(std::string tag, std::string message);

        /**
         * Log verbose message
         *
         * @param tag Tag name
         * @param message Message
         */
        static void verbose(std::string tag, std::string message);

    private:
        /**
         * Dispatch a log message to correct stream, in case of Linux
         * the message is dispatched to stdout and in case of Android
         * the message is dispatched to logcat.
         *
         * @param message Message to dispatch
         */
        static void dispatchMessage(std::string message);
    };
}

#endif //PROJECT_LOGGING_H
