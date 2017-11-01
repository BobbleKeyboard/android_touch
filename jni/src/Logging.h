//
// Created by kunaldawn on 31/10/17.
//

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
