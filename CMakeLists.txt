cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wimplicit-function-declaration")
file(GLOB_RECURSE TOUCH_SRC "jni/src/*.cpp" "jni/src/*.h" "jni/vendor/*.c" "jni/vendor/*.h")

add_executable(touch ${TOUCH_SRC})
target_link_libraries(touch)