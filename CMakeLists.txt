cmake_minimum_required(VERSION 3.10)
project(space2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -march=skylake")

add_executable(space2 main.c Sol.h vector3d.h)
target_link_libraries(space2 SDL2 m)
