cmake_minimum_required(VERSION 3.5)

project(LibFruit)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SUBHOOK_TESTS OFF)
set(SUBHOOK_STATIC ON)
add_subdirectory(subhook)

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

    Memory/Protection.h
    Memory/Protection.cpp
    Memory/Detour/Virtual.h
    Memory/Detour/Virtual.cpp
    Memory/Detour/Memory.h
    Memory/Detour/Memory.cpp
    )

target_include_directories(LibFruit PUBLIC .)
target_compile_definitions(LibFruit PUBLIC LOGURU_USE_FMTLIB)
target_link_libraries(LibFruit PUBLIC subhook)
