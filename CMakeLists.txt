cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -frtti -fexceptions")
file(GLOB_RECURSE TOUCH_SRC "jni/src/*.cpp" "jni/src/*.h" "jni/vendor/*.c" "jni/vendor/*.cpp" "jni/vendor/*.h" "jni/vendor/*.hpp")

add_executable(touch ${TOUCH_SRC})
target_link_libraries(touch)