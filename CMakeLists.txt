cmake_minimum_required(VERSION 3.25)

project(TheBlackHatX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMake mitteilen, wo die Geode-Dateien im Submodul liegen
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/geode-sdk-clone/cmake")

include(Geode)

setup_geode_mod(
    ID com.theblackhatx.mod
    NAME "TheBlackHatX"
    VERSION "1.0.0"
    DEVELOPER "TheBlackHatX"
    DESCRIPTION "Ein krasser Mod von TheBlackHatX"
    SOURCES 
        src/main.cpp
)
