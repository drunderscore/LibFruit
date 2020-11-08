cmake_minimum_required(VERSION 3.5)

project(LibFruit)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(LibFruit STATIC
    Fruit.h
    Types.h
    Result.h
    Log.h

    Graphics/MessageBox.h
    Graphics/MessageBox.cpp

    Data/DataSize.h
    Data/DataSize.cpp
    Data/Parser.h
    Data/Parser.cpp
    Data/Stream.h

    loguru/loguru.hpp
    loguru/loguru.cpp
    )

target_include_directories(LibFruit PUBLIC .)
