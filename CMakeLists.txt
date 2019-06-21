cmake_minimum_required(VERSION 3.14)
project(audio_pitcher)

set(CMAKE_CXX_STANDARD 14)

add_executable(audio_pitcher main.cpp wave.h wave.cpp)