#                  _           _     _   _                   _
#  __ _ _ __   __| |_ __ ___ (_) __| | | |_ ___  _   _  ___| |__
# / _` | '_ \ / _` | '__/ _ \| |/ _` | | __/ _ \| | | |/ __| '_ \
#| (_| | | | | (_| | | | (_) | | (_| | | || (_) | |_| | (__| | | |
# \__,_|_| |_|\__,_|_|  \___/|_|\__,_|  \__\___/ \__,_|\___|_| |_|
#
# Copyright (c) 2017 Kunal Dawn <kunal.dawn@gmail.com>
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 3 as published by
# the Free Software Foundation.

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := android_touch

LOCAL_SRC_FILES := vendor/libevdev/libevdev.c         \
                   vendor/libevdev/libevdev-names.c   \
                   vendor/libevdev/libevdev-uinput.c  \
                   vendor/jsoncpp/jsoncpp.cpp         \
                   src/Logging.cpp                    \
                   src/TouchInput.cpp                 \
                   src/TouchState.cpp                 \
                   src/HTTPServer.cpp                 \

LOCAL_LDLIBS := -latomic -llog

include $(BUILD_EXECUTABLE)