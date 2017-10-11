cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_VERBOSE_MAKEFILE on)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fexceptions -frtti")
file(GLOB_RECURSE TOUCH_SRC "src/*.cpp" "src/*.h")

add_executable(touch ${TOUCH_SRC})
target_link_libraries(touch -levdev)