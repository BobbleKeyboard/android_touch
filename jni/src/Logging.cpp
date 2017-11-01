//
// Created by kunaldawn on 31/10/17.
//

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
