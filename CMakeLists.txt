cmake_minimum_required(VERSION 3.18)

project(TheBlackHatX)

set(CMAKE_CXX_STANDARD 20)

add_library(TheBlackHatX SHARED src/main.cpp)

target_link_libraries(TheBlackHatX PRIVATE Geode::Geode)
