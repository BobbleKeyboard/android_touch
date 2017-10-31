LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := android_touch

LOCAL_SRC_FILES := src/TouchInput.cpp \
                   src/TouchState.cpp \
                   vendor/libevdev/libevdev.c \
                   vendor/libevdev/libevdev-names.c \
                   vendor/libevdev/libevdev-uinput.c \
                   src/main.cpp

LOCAL_LDLIBS := -latomic

include $(BUILD_EXECUTABLE)