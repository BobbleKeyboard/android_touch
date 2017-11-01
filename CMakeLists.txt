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

cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -frtti -fexceptions")
file(GLOB_RECURSE TOUCH_SRC "jni/src/*.cpp" "jni/src/*.h" "jni/vendor/*.c" "jni/vendor/*.cpp" "jni/vendor/*.h" "jni/vendor/*.hpp")

add_executable(android_touch ${TOUCH_SRC})
target_link_libraries(android_touch)