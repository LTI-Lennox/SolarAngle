cmake_minimum_required(VERSION 3.22)
project(solarAngle C)

set(CMAKE_C_STANDARD 99)

add_executable(solarAngle main.c solarAngle/solarAngle.c solarAngle/solarAngle.h)
