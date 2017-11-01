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
                   src/Server.cpp                     \

LOCAL_LDLIBS := -latomic -llog

include $(BUILD_EXECUTABLE)