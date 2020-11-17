cmake_minimum_required(VERSION 3.5)

project(LibFruit)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(LibFruit STATIC
    fmt/format.cc
    fmt/os.cc

    Fruit.h
    Types.h
    Result.h
    Log.h
    Log.cpp

    Graphics/MessageBox.h
    Graphics/MessageBox.cpp

    Data/DataSize.h
    Data/DataSize.cpp
    Data/Parser.h
    Data/Parser.cpp
    Data/Stream.h
    )

target_include_directories(LibFruit PRIVATE .)
target_compile_definitions(LibFruit PRIVATE LOGURU_USE_FMTLIB)