cmake_minimum_required(VERSION 3.18)

project(TheBlackHatX)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_CURRENT_SOURCE_DIR}/geode-sdk-clone/cmake/Geode.cmake)

setup_geode_mod(
    ID com.theblackhatx.mod
    NAME TheBlackHatX
    VERSION 1.0.0
    SOURCES src/main.cpp
)
